/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginConstants.h"

//==============================================================================
/**
*/
class BiQuadAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BiQuadAudioProcessor();
    ~BiQuadAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	AudioProcessorValueTreeState& getVts() { return parameters; }
	float getSampleRate() { return sampleRate; }
	float* getFFTData() { return fftData; }
	bool isNextFFTBlockReady() { return nextFFTBlockReady; }
	void setNextFFTBlockReady(bool ready) { nextFFTBlockReady = ready; }

	//==============================================================================
	void updateFilterParameters();
private:
	
	//==============================================================================
	// Raw property values
	float* cutoff;
	float* q;
	float* filterDesign;
	float* filterType;
	
	float sampleRate;
	homedsp::IIRFilters filter;
	AudioProcessorValueTreeState parameters;

	int fifoIndex = 0;
	float fifo[Analyzer::fftSize];
	float fftData[2 * Analyzer::fftSize];
	bool nextFFTBlockReady = false;

	//==============================================================================
	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
	void pushNextSampleIntoFifo(float sample);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BiQuadAudioProcessor)
};
