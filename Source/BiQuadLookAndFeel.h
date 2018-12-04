/*
  ==============================================================================

    BiQuadLookAndFeel.h
    Created: 30 Nov 2018 6:49:18pm
    Author:  Family

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class BiQuadLookAndFeel : public LookAndFeel_V4
{

public:

	BiQuadLookAndFeel();

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;

	Font getComboBoxFont(ComboBox& box) override;
};