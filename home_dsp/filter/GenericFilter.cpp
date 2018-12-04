/*
  ==============================================================================

    GenericFilter.cpp
    Created: 2 Dec 2018 1:41:26pm
    Author:  Family

  ==============================================================================
*/

#include "JuceHeader.h"
#include "GenericFilter.h"

using homedsp::GenericFilter;

void GenericFilter::calculateLPF()
{
	float centerFrequency = 2.0f * float_Pi * cutoff / sampleRate;
	float d = 1.0f / q;
	float beta = 0.5f * ((1.0f - d * sin(centerFrequency)) / 2.0f) / ((1.0f + d * sin(centerFrequency)) / 2.0f);
	float gamma = (0.5f + beta) * cos(centerFrequency);

	a0 = (0.5f + beta - gamma) / 2.0f;
	a1 = 0.5f + beta - gamma;
	a2 = a0;
	b1 = -2.0f * gamma;
	b2 = 2.0f * beta;
}

void GenericFilter::calculateHPF()
{
	float centerFrequency = 2.0f * float_Pi * cutoff / sampleRate;
	float d = 1.0f / q;
	float beta = 0.5f * ((1.0f - d * sin(centerFrequency)) / 2.0f) / ((1.0f + d * sin(centerFrequency)) / 2.0f);
	float gamma = (0.5f + beta) * cos(centerFrequency);

	a0 = (0.5f + beta + gamma) / 2.0f;
	a1 = -(0.5f + beta + gamma);
	a2 = a0;
	b1 = -2.0f * gamma;
	b2 = 2.0f * beta;
}

void GenericFilter::calculateBPF()
{
	float centerFrequency = 2.0f * float_Pi * cutoff / sampleRate;
	float d = 1.0f / q;
	float beta = 0.5f * (1.0f - tan(centerFrequency / (2.0f * q))) / (1.0f + tan(centerFrequency / (2.0f * q)));
	float gamma = (0.5f + beta) * cos(centerFrequency);

	a0 = 0.5f - beta;
	a1 = 0.0;
	a2 = -(0.5f - beta);
	b1 = -2.0f * gamma;
	b2 = 2.0f * beta;
}

void GenericFilter::calculateBSF()
{
	float centerFrequency = 2.0f * float_Pi * cutoff / sampleRate;
	float d = 1.0f / q;
	float beta = 0.5f * (1.0f - tan(centerFrequency / (2.0f * q))) / (1.0f + tan(centerFrequency / (2.0f * q)));
	float gamma = (0.5f + beta) * cos(centerFrequency);

	a0 = 0.5f + beta;
	a1 = -2.0f * gamma;
	a2 = 0.5f + beta;
	b1 = -2.0f * gamma;
	b2 = 2.0f * beta;
}