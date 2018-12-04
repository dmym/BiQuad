/*
  ==============================================================================

    SpectrumComponent.h
    Created: 30 Nov 2018 6:48:45pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h" 
#include "PluginConstants.h"

//==============================================================================
/*
*/
class SpectrumComponent    : public Component, Timer
{
public:
    SpectrumComponent(BiQuadAudioProcessor& p);
    ~SpectrumComponent();

    void paint (Graphics&) override;
    void resized() override;
	void timerCallback() override;

private:

	float* fftData;
	int fftBins[Analyzer::scopeSize];
	float scopeData[Analyzer::scopeSize];

	BiQuadAudioProcessor& processor;
	dsp::FFT forwardFFT;
	dsp::WindowingFunction<float> window;

	//==============================================================================
	void drawNextFrameOfSpectrum();
	void drawFrame(Graphics& g);

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumComponent)
};
