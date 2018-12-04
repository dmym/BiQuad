/*
  ==============================================================================

    AnalyzerComponent.h
    Created: 30 Nov 2018 6:48:27pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SpectrumComponent.h"

//==============================================================================
/*
*/
class AnalyzerComponent    : public Component
{
public:
    AnalyzerComponent(BiQuadAudioProcessor& p);
    ~AnalyzerComponent();

    void paint (Graphics&) override;
    void resized() override;

private:

	SpectrumComponent spectrumBlock;
	Rectangle<int> analyzerWindow;
	
	//==============================================================================
	void drawLineForFrequency(Graphics& g, float freq);
	void drawLineFordB(Graphics& g, int dB);

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyzerComponent)
};
