/*
  ==============================================================================

    IIRFilterBase.cpp
    Created: 2 Dec 2018 1:37:38pm
    Author:  Family

  ==============================================================================
*/

#include "IIRFilterBase.h"

using homedsp::IIRFilterBase;
using homedsp::IIRType;
using homedsp::ChannelFeed;

void IIRFilterBase::updateFilterCoefficients(float cutoff, float q, float sampleRate, IIRType filterType)
{
	this->cutoff = cutoff;
	this->q = q;
	this->sampleRate = sampleRate;

	switch (filterType)
	{
	case IIRType::LPF: calculateLPF(); break;
	case IIRType::HPF: calculateHPF(); break;
	case IIRType::BPF: calculateBPF(); break;
	case IIRType::BSF: calculateBSF(); break;
	}
}

float IIRFilterBase::applyFiltering(float xn, ChannelFeed& c)
{
	float yn = a0 * xn + a1 * c.xn_1 + a2 * c.xn_2 - b1 * c.yn_1 - b2 * c.yn_2;

	c.xn_2 = c.xn_1;
	c.xn_1 = xn;

	c.yn_2 = c.yn_1;
	c.yn_1 = yn;

	return yn;
}