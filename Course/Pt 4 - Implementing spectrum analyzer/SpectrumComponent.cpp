/*
  ==============================================================================

    SpectrumComponent.cpp
    Created: 30 Nov 2018 6:48:45pm
    Author:  Family

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectrumComponent.h"

//==============================================================================
SpectrumComponent::SpectrumComponent(BiQuadAudioProcessor& p) :
	processor(p),
	forwardFFT(Analyzer::fftOrder),
	window(Analyzer::fftOrder, dsp::WindowingFunction<float>::kaiser),
	fftData(p.getFFTData())
{
	startTimerHz(Analyzer::framePeriodHz);

	// define fft bins to use during rendering
	for (int i = 0; i < Analyzer::scopeSize; i++)
	{
		auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - i / (float)Analyzer::scopeSize) * 0.4f);
		auto fftDataIndex = jlimit(0, Analyzer::fftSize / 2, (int)(skewedProportionX * Analyzer::fftSize / 2));
		fftBins[i] = fftDataIndex;
	}
}

SpectrumComponent::~SpectrumComponent()
{
}

void SpectrumComponent::paint (Graphics& g)
{
	g.setColour(PluginColours::greyBright);
	drawFrame(g);
}

void SpectrumComponent::resized()
{

}

void SpectrumComponent::timerCallback()
{
	if (processor.isNextFFTBlockReady())
	{
		drawNextFrameOfSpectrum();
		processor.setNextFFTBlockReady(false);
		repaint();
	}
}

void SpectrumComponent::drawNextFrameOfSpectrum()
{
	window.multiplyWithWindowingTable(fftData, Analyzer::fftSize);
	forwardFFT.performFrequencyOnlyForwardTransform(fftData);

	auto mindB = (float)Analyzer::dBRange.getStart();
	auto maxdB = (float)Analyzer::dBRange.getEnd();

	for (int i = 0; i < Analyzer::scopeSize; ++i)
	{
		auto fftBin = fftBins[i];

		// convert fft bin value to dB and map to the range [ 0; 1 ]
		auto level = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftData[fftBin])
			- Decibels::gainToDecibels((float)Analyzer::fftSize)),
			mindB, maxdB, 0.0f, 1.0f);

		scopeData[i] = level;
	}
}

void SpectrumComponent::drawFrame(Graphics& g)
{
	auto width = getLocalBounds().getWidth();
	auto height = getLocalBounds().getHeight();
	auto startFreq = Analyzer::frequencyRange.getStart();
	auto endFreq = Analyzer::frequencyRange.getEnd();
	auto sampleRate = processor.getSampleRate();
	auto x_1 = 0.0f;

	for (int i = 0; i < Analyzer::scopeSize; ++i)
	{
		auto fftBin = fftBins[i];

		// get point frequency from FFT bin number
		auto freq = fftBin * sampleRate / Analyzer::fftSize;

		if (freq >= startFreq && freq <= endFreq)
		{
			auto x = width * std::log10(freq / startFreq) / std::log10(endFreq / startFreq);

			g.drawLine({ x_1, jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
						x, jmap(scopeData[i], 0.0f, 1.0f, (float)height, 0.0f) });

			x_1 = x;
		}
	}
}