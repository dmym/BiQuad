/*
  ==============================================================================

    BiQuadLookAndFeel.cpp
    Created: 30 Nov 2018 6:49:18pm
    Author:  Family

  ==============================================================================
*/

#include "BiQuadLookAndFeel.h"
#include "PluginConstants.h"

BiQuadLookAndFeel::BiQuadLookAndFeel()
{
	setColour(Label::textColourId, PluginColours::white);
	setColour(ComboBox::ColourIds::backgroundColourId, PluginColours::greyDark);
	setColour(ComboBox::ColourIds::outlineColourId, PluginColours::whiteRed);
	setColour(ResizableWindow::backgroundColourId, PluginColours::greyDark);
}

void BiQuadLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	// draw outer rim
	g.setColour(PluginColours::whiteRed);

	Path outerRim;
	outerRim.addStar(Point<float>(bounds.getCentreX(), bounds.getCentreY()), 15, radius - 1.0f, radius, toAngle);
	g.fillPath(outerRim);

	// draw inner ellipse
	g.setColour(PluginColours::white);

	auto innerEllipseRadius = radius - radius / 5.0f;
	g.fillEllipse(
		bounds.getCentreX() - innerEllipseRadius,
		bounds.getCentreY() - innerEllipseRadius,
		innerEllipseRadius * 2.0f,
		innerEllipseRadius * 2.0f
	);

	g.setColour(PluginColours::brownRed);

	// draw pointer
	Path pointer;
	auto pointerLength = radius * 0.4f;
	auto pointerThickness = 2.0f;
	auto pointerX = -pointerThickness * 0.5;
	auto pointerY = -innerEllipseRadius;

	pointer.addRectangle(
		pointerX,
		pointerY,
		pointerThickness,
		pointerLength
	);

	pointer.applyTransform(AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));
	g.fillPath(pointer);
}

Font BiQuadLookAndFeel::getComboBoxFont(ComboBox & box)
{
	return Font(14.0f);
}