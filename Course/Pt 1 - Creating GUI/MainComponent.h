/*
  ==============================================================================

    MainComponent.h
    Created: 30 Nov 2018 7:41:16pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnalyzerComponent.h"
#include "KnobsComponent.h"
#include "BiQuadLookAndFeel.h"

//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:

	BiQuadLookAndFeel lcf;

	// Child components
	AnalyzerComponent analyzerBlock;
	KnobsComponent knobsBlock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
