/*
  ==============================================================================

    AnalyzerComponent.cpp
    Created: 30 Nov 2018 6:48:27pm
    Author:  Family

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnalyzerComponent.h"

//==============================================================================
AnalyzerComponent::AnalyzerComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AnalyzerComponent::~AnalyzerComponent()
{
}

void AnalyzerComponent::paint (Graphics& g)
{
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("AnalyzerComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void AnalyzerComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
