/*
  ==============================================================================

    KnobsComponent.h
    Created: 30 Nov 2018 6:48:57pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class KnobsComponent    : public Component
{
public:
    KnobsComponent();
    ~KnobsComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
	
	// Design combobox
	ComboBox designCombo;
	Label designComboLabel;

	// Type combobox
	ComboBox typeCombo;
	Label typeComboLabel;

	// Cutoff knob
	Slider cutoffKnob{ Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
	Label cutoffKnobLabel;


	// Q knob
	Slider qKnob{ Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };;
	Label qKnobLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobsComponent)
};
