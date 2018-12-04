/*
  ==============================================================================

	AnalyzerComponent.cpp
	Created: 30 Nov 2018 6:48:27pm
	Author:  Family

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginConstants.h"
#include "AnalyzerComponent.h"

//==============================================================================
AnalyzerComponent::AnalyzerComponent(BiQuadAudioProcessor& p) : 
	spectrumBlock(p)
{
	addAndMakeVisible(spectrumBlock);
}

AnalyzerComponent::~AnalyzerComponent()
{
}

void AnalyzerComponent::paint(Graphics& g)
{
	g.setColour(PluginColours::grey);
	g.fillRect(analyzerWindow);

	g.setColour(PluginColours::greyWarm);
	g.drawRect(analyzerWindow);

	g.setFont(10);

	// draw frequency lines
	for (int i = 0; i < Analyzer::plotFrequenciesNum; i++)
	{
		drawLineForFrequency(g, Analyzer::plotFrequencies[i]);
	}

	// draw dB lines
	for (int i = Analyzer::dBRange.getStart(), n = Analyzer::dBRange.getEnd(); i < n; i += Analyzer::plotdBPeriod)
	{
		drawLineFordB(g, i);
	}
}

void AnalyzerComponent::resized()
{
	analyzerWindow = getLocalBounds().reduced(30, 20).translated(10, 0);
	spectrumBlock.setBounds(analyzerWindow);
}

//==============================================================================
void AnalyzerComponent::drawLineForFrequency(Graphics& g, float freq)
{
	auto startFreq = Analyzer::frequencyRange.getStart();
	auto endFreq = Analyzer::frequencyRange.getEnd();

	// define line coordinates
	auto x = analyzerWindow.getX() + analyzerWindow.getWidth() * std::log10(freq / startFreq) / std::log10(endFreq / startFreq);
	auto startY = analyzerWindow.getY();
	auto endY = analyzerWindow.getY() + analyzerWindow.getHeight();

	// draw line
	g.setColour(PluginColours::greyWarm);
	g.drawLine(x, startY, x, endY, 1.0f);

	// create label text
	// if frequency is more or equal to 1000, shrink value and add 'K' prefix
	String label = freq < 1000.0f ? String(freq) : String(freq / 1000) + "K";

	// draw line label
	g.setColour(PluginColours::white);
	g.drawText(label, x - 20, endY + 1, 40, 20, Justification::centred);
}

void AnalyzerComponent::drawLineFordB(Graphics& g, int dB)
{
	// define line coordinates
	auto startX = analyzerWindow.getX();
	auto endX = startX + analyzerWindow.getWidth();
	auto y = jmap(dB, Analyzer::dBRange.getStart(), Analyzer::dBRange.getEnd(), analyzerWindow.getY() + analyzerWindow.getHeight(), analyzerWindow.getY());

	// draw line
	g.setColour(PluginColours::greyWarm);
	g.drawLine(startX, y, endX, y, 0.3f);

	// draw label
	g.setColour(PluginColours::white);
	g.drawText(String(dB) + " dB", startX - 40, y - 20, 35, 20, Justification::bottomRight);
}