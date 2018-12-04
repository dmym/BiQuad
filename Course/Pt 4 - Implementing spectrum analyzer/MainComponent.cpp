/*
  ==============================================================================

    MainComponent.cpp
    Created: 30 Nov 2018 7:41:16pm
    Author:  Family

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(BiQuadAudioProcessor& p) :
	knobsBlock(p), analyzerBlock(p)
{
	setLookAndFeel(&lcf);

	addAndMakeVisible(analyzerBlock);
	addAndMakeVisible(knobsBlock);
}

MainComponent::~MainComponent()
{
	setLookAndFeel(nullptr);
}

void MainComponent::paint (Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
	auto area = getLocalBounds();
	knobsBlock.setBounds(area.removeFromBottom(getHeight() * 0.3f));
	analyzerBlock.setBounds(area);
}
