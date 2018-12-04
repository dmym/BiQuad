/*
  ==============================================================================

    IIRFilters.cpp
    Created: 2 Dec 2018 1:44:27pm
    Author:  Family

  ==============================================================================
*/

#include "IIRFilters.h"

using homedsp::IIRFilters;
using homedsp::ChannelFeed;
using homedsp::IIRType;
using homedsp::IIRDesign;

IIRFilters::IIRFilters(int channels) :
	channelsNum(channels)
{
	for (auto i = 0; i < channelsNum; i++)
	{
		channelFeeds.add(new ChannelFeed);
	}
}

IIRFilters::~IIRFilters()
{

}

ChannelFeed & IIRFilters::getChannelFeed(int channelNum)
{
	return *channelFeeds[channelNum];
}

void IIRFilters::setFilterParameters(float cutoff, float q, IIRType filterType, IIRDesign filterDesign, float sampleRate)
{
	switch (filterDesign)
	{
	case IIRDesign::Generic: activeFilter = &gFilter; break;
	case IIRDesign::Butterworth: activeFilter = &butterFilter; break;
	case IIRDesign::LinkwitzRiley: activeFilter = &linkwitzRileyFilter; break;
	default: activeFilter = &gFilter;
	}

	activeFilter->updateFilterCoefficients(cutoff, q, sampleRate, filterType);
}

float IIRFilters::applyFiltering(float xn, ChannelFeed& c)
{
	if (activeFilter == nullptr)
		return xn;

	return activeFilter->applyFiltering(xn, c);
}