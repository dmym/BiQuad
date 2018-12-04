/*
  ==============================================================================

    KnobsComponent.cpp
    Created: 30 Nov 2018 6:48:57pm
    Author:  Family

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KnobsComponent.h"

//==============================================================================
KnobsComponent::KnobsComponent(BiQuadAudioProcessor& p) :
	processor(p)
{
	Font font(14.0f);
	auto& vts = processor.getVts();

	// Filter Design ComboBox
	designCombo.addItemList({ "Generic", "Butterworth", "Linkwitz-Riley" }, 1);
	designCombo.onChange = [this] { filterDesignChanged(); processor.updateFilterParameters(); };
	designComboAttachment.reset(new ComboBoxAttachment(vts, "filterDesign", designCombo));
	addAndMakeVisible(designCombo);

	designComboLabel.setText("Design:", dontSendNotification);
	designComboLabel.setFont(font);
	designComboLabel.setJustificationType(Justification::centredLeft);
	designComboLabel.attachToComponent(&designCombo, false);
	addAndMakeVisible(designComboLabel);

	// Filter Type ComboBox
	typeCombo.addItemList({ "LPF", "HPF", "BPF", "BSF" }, 1);
	typeCombo.onChange = [this] { processor.updateFilterParameters(); };
	typeComboAttachment.reset(new ComboBoxAttachment(vts, "filterType", typeCombo));
	addAndMakeVisible(typeCombo);

	typeComboLabel.setText("Type:", dontSendNotification);
	typeComboLabel.setFont(font);
	typeComboLabel.setJustificationType(Justification::centredLeft);
	typeComboLabel.attachToComponent(&typeCombo, false);
	addAndMakeVisible(typeComboLabel);

	// Cutoff Knob
	cutoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, cutoffKnob.getTextBoxWidth(), cutoffKnob.getTextBoxHeight());
	cutoffKnob.onValueChange = [this] { processor.updateFilterParameters(); };
	cutoffAttacment.reset(new SliderAttachment(vts, "cutoff", cutoffKnob));
	addAndMakeVisible(cutoffKnob);

	cutoffKnobLabel.setText("Cutoff", dontSendNotification);
	cutoffKnobLabel.setFont(font);
	cutoffKnobLabel.setJustificationType(Justification::centred);
	cutoffKnobLabel.attachToComponent(&cutoffKnob, false);
	addAndMakeVisible(cutoffKnobLabel);

	// Q Knob
	qKnob.setTextBoxStyle(Slider::TextBoxBelow, false, qKnob.getTextBoxWidth(), qKnob.getTextBoxHeight());
	qKnob.onValueChange = [this] { processor.updateFilterParameters(); };
	qAttacment.reset(new SliderAttachment(vts, "q", qKnob));
	addAndMakeVisible(qKnob);

	qKnobLabel.setText("Q", dontSendNotification);
	qKnobLabel.setFont(font);
	qKnobLabel.setJustificationType(Justification::centred);
	qKnobLabel.attachToComponent(&qKnob, false);
	addAndMakeVisible(qKnobLabel);

	filterDesignChanged();
}

KnobsComponent::~KnobsComponent()
{
}

void KnobsComponent::paint (Graphics& g)
{
	
}

void KnobsComponent::resized()
{
	auto area = getLocalBounds();
	area.removeFromTop(20);

	// ComboBoxes
	auto comboArea = area.removeFromLeft(getWidth() / 3).withTrimmedLeft(40);
	int comboBoxHeight = jmin(60, comboArea.getHeight() / 2);

	designCombo.setBounds(comboArea.removeFromTop(comboBoxHeight).reduced(0, 10));
	typeCombo.setBounds(comboArea.removeFromTop(comboBoxHeight).reduced(0, 10));

	// Knobs
	auto knobArea = area.reduced(area.getWidth() / 5, 0).reduced(10);
	auto knobAreaMedian = knobArea.getWidth() / 2;
	auto knobWidth = jmin(100, knobAreaMedian);
	auto knobHeight = jmin(100, knobArea.getHeight());
	auto knob = knobArea.withWidth(knobWidth).withHeight(knobHeight);

	cutoffKnob.setBounds(knob);
	qKnob.setBounds(knob.translated(knobAreaMedian, 0));
}

//==============================================================================
void KnobsComponent::filterDesignChanged()
{
	switch (designCombo.getSelectedItemIndex())
	{
		case homedsp::IIRDesign::Generic:
		{
			qKnob.setEnabled(true);
			setBandItemsEnabled(true);
		} break;

		case homedsp::IIRDesign::Butterworth:
		{
			qKnob.setEnabled(false);
			setBandItemsEnabled(true);
		} break;

		case homedsp::IIRDesign::LinkwitzRiley:
		{
			qKnob.setEnabled(false);

			auto selectedType = typeCombo.getSelectedItemIndex();

			if (selectedType == homedsp::IIRType::BPF || selectedType == homedsp::IIRType::BSF)
				typeCombo.setSelectedItemIndex(homedsp::IIRType::LPF);

			setBandItemsEnabled(false);
		} break;
	}
}

void KnobsComponent::setBandItemsEnabled(bool isEnabled)
{
	typeCombo.setItemEnabled(homedsp::IIRType::BPF + 1, isEnabled);
	typeCombo.setItemEnabled(homedsp::IIRType::BSF + 1, isEnabled);
}