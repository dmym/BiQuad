/*
  ==============================================================================

    SpectrumComponent.h
    Created: 30 Nov 2018 6:48:45pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SpectrumComponent    : public Component
{
public:
    SpectrumComponent();
    ~SpectrumComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumComponent)
};
