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
	// init value tree to maintain plugin's size state
	initPluginSizeValueTree();

	setResizable(true, true);

	setSize(
		pluginSizeVt.getProperty(PluginIdentifiers::width),
		pluginSizeVt.getProperty(PluginIdentifiers::height)
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
	pluginSizeVt.setProperty(PluginIdentifiers::width, getWidth(), nullptr);
	pluginSizeVt.setProperty(PluginIdentifiers::height, getHeight(), nullptr);
}

void BiQuadAudioProcessorEditor::initPluginSizeValueTree()
{
	// get or create value tree that holds plugin size info
	auto& vts = processor.getVts();
	pluginSizeVt = vts.state.getOrCreateChildWithName(PluginIdentifiers::pluginSize, nullptr);

	// if value tree is empty, add properies for plugin's width and height values
	if (!pluginSizeVt.isValid())
	{
		pluginSizeVt.setProperty(PluginIdentifiers::width, PluginSize::minWidth, nullptr);
		pluginSizeVt.setProperty(PluginIdentifiers::height, PluginSize::minHeight, nullptr);
	}
}