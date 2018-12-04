/*
  ==============================================================================

    IIRFilters.h
    Created: 2 Dec 2018 1:44:27pm
    Author:  Family

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "IIRFilterBase.h"
#include "GenericFilter.h"
#include "ButterworthFilter.h"
#include "LinkwitzRileyFilter.h"

namespace homedsp 
{
	class IIRFilters
	{
	public:
		IIRFilters(int channelsNum);
		~IIRFilters();

		ChannelFeed& getChannelFeed(int channelNum);
		void setFilterParameters(float cutoff, float q, IIRType filterType, IIRDesign filterDesign, float sampleRate);
		float applyFiltering(float xn, ChannelFeed& channel);

	private:
		int channelsNum;
		juce::OwnedArray<ChannelFeed> channelFeeds;

		// filters
		GenericFilter gFilter;
		ButterworthFilter butterFilter;
		LinkwitzRileyFilter linkwitzRileyFilter;

		IIRFilterBase* activeFilter;
	};
}
