/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MainComponent.h"
#include "PluginConstants.h"

//==============================================================================
/**
*/
class BiQuadAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    BiQuadAudioProcessorEditor (BiQuadAudioProcessor&);
    ~BiQuadAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BiQuadAudioProcessor& processor;
	ValueTree pluginSizeVt;
	
	// Child components
	MainComponent mainBlock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BiQuadAudioProcessorEditor)
};
