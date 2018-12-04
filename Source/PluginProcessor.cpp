/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginConstants.h"

//==============================================================================
BiQuadAudioProcessor::BiQuadAudioProcessor() :
	parameters(*this, nullptr, PluginIdentifiers::baseType, createParameterLayout()),
	filter(getTotalNumInputChannels()),
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::stereo(), true)
		.withOutput("Output", AudioChannelSet::stereo(), true))

{
	cutoff = parameters.getRawParameterValue("cutoff");
	q = parameters.getRawParameterValue("q");
	filterDesign = parameters.getRawParameterValue("filterDesign");
	filterType = parameters.getRawParameterValue("filterType");
}

BiQuadAudioProcessor::~BiQuadAudioProcessor()
{
}

//==============================================================================
const String BiQuadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BiQuadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BiQuadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BiQuadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BiQuadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BiQuadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BiQuadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BiQuadAudioProcessor::setCurrentProgram (int index)
{
}

const String BiQuadAudioProcessor::getProgramName (int index)
{
    return {};
}

void BiQuadAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BiQuadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	this->sampleRate = sampleRate;
	updateFilterParameters();
}

void BiQuadAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Pt1BuildGuiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BiQuadAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
		homedsp::ChannelFeed& channelFeed = filter.getChannelFeed(channel);

		for (auto sample = 0, n = buffer.getNumSamples(); sample < n; ++sample)
		{
			auto yn = filter.applyFiltering(*channelData, channelFeed);

			*channelData = yn;
			channelData++;

			pushNextSampleIntoFifo(yn);
		}
	}
}

void BiQuadAudioProcessor::pushNextSampleIntoFifo(float sample)
{
	if (fifoIndex == Analyzer::fftSize)
	{
		if (!nextFFTBlockReady)
		{
			zeromem(fftData, sizeof(fftData));
			memcpy(fftData, fifo, sizeof(fifo));
			nextFFTBlockReady = true;
		}

		fifoIndex = 0;
	}

	fifo[fifoIndex++] = sample;
}

//==============================================================================
bool BiQuadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BiQuadAudioProcessor::createEditor()
{
    return new BiQuadAudioProcessorEditor (*this);
}

//==============================================================================
void BiQuadAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void BiQuadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void BiQuadAudioProcessor::updateFilterParameters()
{
	auto type = static_cast<homedsp::IIRType>(static_cast<int>(*filterType));
	auto design = static_cast<homedsp::IIRDesign>(static_cast<int>(*filterDesign));
	filter.setFilterParameters(*cutoff, *q, type, design, sampleRate);
}

AudioProcessorValueTreeState::ParameterLayout BiQuadAudioProcessor::createParameterLayout()
{
	return
	{
		std::make_unique<AudioParameterFloat>
		(
			"cutoff",
			"Cutoff",
			NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.4f, false),
			3500.0f,
			"Hz"
		),
		std::make_unique<AudioParameterFloat>
		(
			"q",
			"Q",
			NormalisableRange<float>(1.0f, 10.0f, 0.1f),
			1.0f
		),
		std::make_unique<AudioParameterChoice>
		(
			"filterDesign",
			"Filter Design",
			StringArray { "Generic", "Butterworth", "Linkwitz-Riley" },
			0
		),
		std::make_unique<AudioParameterChoice>
		(
			"filterType",
			"Filter Type",
			StringArray { "LPF", "HPF", "BPF", "BSF" },
			0
		)
	};
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BiQuadAudioProcessor();
}
