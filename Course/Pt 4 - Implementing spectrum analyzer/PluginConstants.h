/*
  ==============================================================================

    PluginConstants.h
    Created: 2 Dec 2018 12:27:12pm
    Author:  Family

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace PluginColours
{
	static const Colour white = Colour(0xffeff2f5);
	static const Colour whiteRed = Colour(0xffd9d9d9);
	static const Colour grey = Colour(0xff414b50);
	static const Colour greyWarm = Colour(0xff61676b);
	static const Colour greyBright = Colour(0xff959b9f);
	static const Colour greyDark = Colour(0xff323d42);
	static const Colour brownRed = Colour(0xff734f20);
}

namespace PluginIdentifiers
{
	static const Identifier baseType("BiQuadFilter");
	static const Identifier pluginSize("PluginSize");
	static const Identifier width("Width");
	static const Identifier height("Height");
}

namespace PluginSize
{
	static const int minWidth = 600;
	static const int minHeight = 400;
	static const int maxWidth = 1000;
	static const int maxHeight = 800;
}

namespace Analyzer
{
	static const float plotFrequencies[] = { 20.0f, 50.0f, 100.0f, 200.0f, 500.0f, 1000.0f, 2000.0f, 5000.0f, 10000.0f, 20000.0f };
	static const int plotFrequenciesNum = sizeof(plotFrequencies)/sizeof(plotFrequencies[0]);
	static const int plotdBPeriod = 12;
	static const Range<float> frequencyRange(20.0f, 20000.0f);
	static const Range<int> dBRange(-96, 12);
	static const int scopeSize = 128;
	static const int framePeriodHz = 30;

	// fft
	static const int fftOrder = 11;
	static const int fftSize = 1 << fftOrder;
}
