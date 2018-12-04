/*
  ==============================================================================

    AnalyzerComponent.h
    Created: 30 Nov 2018 6:48:27pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AnalyzerComponent    : public Component
{
public:
    AnalyzerComponent();
    ~AnalyzerComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyzerComponent)
};
