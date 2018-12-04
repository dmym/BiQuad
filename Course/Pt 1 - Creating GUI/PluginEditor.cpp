/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BiQuadAudioProcessorEditor::BiQuadAudioProcessorEditor (BiQuadAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mainBlock(p)
{
	setResizable(true, true);

	setSize(
		PluginSize::minWidth, 
		PluginSize::minHeight
	);

	setResizeLimits(
		PluginSize::minWidth,
		PluginSize::minHeight, 
		PluginSize::maxWidth,
		PluginSize::maxHeight
	);

	getConstrainer()->setFixedAspectRatio(1.5);

	addAndMakeVisible(mainBlock);
}

BiQuadAudioProcessorEditor::~BiQuadAudioProcessorEditor()
{
}

//==============================================================================
void BiQuadAudioProcessorEditor::paint (Graphics& g)
{
    
}

void BiQuadAudioProcessorEditor::resized()
{
	mainBlock.setBounds(getLocalBounds());
}