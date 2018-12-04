/*
  ==============================================================================

    KnobsComponent.h
    Created: 30 Nov 2018 6:48:57pm
    Author:  Family

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

//==============================================================================
/*
*/
class KnobsComponent    : public Component
{
public:
    KnobsComponent(BiQuadAudioProcessor& p);
    ~KnobsComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
	BiQuadAudioProcessor& processor;

	// Design combobox
	ComboBox designCombo;
	Label designComboLabel;
	std::unique_ptr<ComboBoxAttachment> designComboAttachment;

	// Type combobox
	ComboBox typeCombo;
	Label typeComboLabel;
	std::unique_ptr<ComboBoxAttachment> typeComboAttachment;

	// Cutoff knob
	Slider cutoffKnob{ Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
	Label cutoffKnobLabel;
	std::unique_ptr<SliderAttachment> cutoffAttacment;

	// Q knob
	Slider qKnob{ Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };;
	Label qKnobLabel;
	std::unique_ptr<SliderAttachment> qAttacment;

	//==============================================================================
	void updateFilterDesign();
	void setBandItemsEnabled(bool isEnabled);

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobsComponent)
};
