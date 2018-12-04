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
	parameters(*this, nullptr, PluginIdentifiers::baseType, createParameterLayout())
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

BiQuadAudioProcessor::~BiQuadAudioProcessor()
{
	cutoff = parameters.getRawParameterValue("cutoff");
	q = parameters.getRawParameterValue("q");
	filterDesign = parameters.getRawParameterValue("filterDesign");
	filterType = parameters.getRawParameterValue("filterType");
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
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
