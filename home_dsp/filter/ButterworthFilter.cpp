/*
  ==============================================================================

    ButterworthFilter.cpp
    Created: 2 Dec 2018 1:43:37pm
    Author:  Family

  ==============================================================================
*/

#include "JuceHeader.h"
#include "ButterworthFilter.h"

using homedsp::ButterworthFilter;

void ButterworthFilter::calculateLPF()
{
	float c = 1.0f / std::tan(float_Pi * cutoff / sampleRate);
	float cSquare = pow(c, 2.0f);
	float sqrtOfTwo = std::sqrt(2.0f);

	a0 = 1.0f / (1 + sqrtOfTwo * c + cSquare);
	a1 = 2.0f * a0;
	a2 = a0;
	b1 = 2.0f * a0 * (1 - cSquare);
	b2 = a0 * (1 - sqrtOfTwo * c + cSquare);
}

void ButterworthFilter::calculateHPF()
{
	float c = std::tan(float_Pi * cutoff / sampleRate);
	float cSquare = pow(c, 2.0f);
	float sqrtOfTwo = std::sqrt(2.0f);

	a0 = 1.0f / (1 + sqrtOfTwo * c + cSquare);
	a1 = -2.0f * a0;
	a2 = a0;
	b1 = 2.0f * a0 * (cSquare - 1);
	b2 = a0 * (1 - sqrtOfTwo * c + cSquare);
}

void ButterworthFilter::calculateBPF()
{
	float bw = jmin(sampleRate * 0.95f / 2.0f, cutoff / 0.707f);
	float c = 1.0f / std::tan(float_Pi * bw / sampleRate);
	float d = 2.0f * cos(2.0f * float_Pi * cutoff / sampleRate);

	a0 = 1.0f / (1.0f + c);
	a1 = 0.0f;
	a2 = -a0;
	b1 = -a0 * c * d;
	b2 = a0 * (c - 1.0f);
}

void ButterworthFilter::calculateBSF()
{
	float bw = jmin(sampleRate * 0.95f / 2.0f, cutoff / 0.707f);
	float c = std::tan(float_Pi * bw / sampleRate);
	float d = 2.0f * cos(2.0f * float_Pi * cutoff / sampleRate);

	a0 = 1.0f / (1.0f + c);
	a1 = -a0 * d;
	a2 = a0;
	b1 = -a0 * d;
	b2 = a0 * (1.0f - c);
}