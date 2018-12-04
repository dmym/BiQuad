/*
  ==============================================================================

    LinkwitzRileyFilter.cpp
    Created: 2 Dec 2018 1:43:53pm
    Author:  Family

  ==============================================================================
*/

#include "JuceHeader.h"
#include "LinkwitzRileyFilter.h"

using homedsp::LinkwitzRileyFilter;

void LinkwitzRileyFilter::calculateLPF()
{
	float teta = float_Pi * cutoff / sampleRate;
	float omega = float_Pi * cutoff;
	float k = omega / std::tan(teta);
	float k_square = std::pow(k, 2.0f);
	float omega_square = std::pow(omega, 2.0f);
	float sigma = k_square + omega_square + 2.0f * k * omega;

	a0 = omega_square / sigma;
	a1 = 2.0f * a0;
	a2 = a0;
	b1 = (-2.0f * k_square + 2.0f * omega_square) / sigma;
	b2 = (-2.0f * k * omega + k_square + omega_square) / sigma;
}

void LinkwitzRileyFilter::calculateHPF()
{
	float teta = float_Pi * cutoff / sampleRate;
	float omega = float_Pi * cutoff;
	float k = omega / std::tan(teta);
	float k_square = std::pow(k, 2.0f);
	float omega_square = std::pow(omega, 2.0f);
	float sigma = k_square + omega_square + 2.0f * k * omega;

	a0 = k_square / sigma;
	a1 = -2.0f * a0;
	a2 = a0;
	b1 = (-2.0f * k_square + 2.0f * omega_square) / sigma;
	b2 = (-2.0f * k * omega + k_square + omega_square) / sigma;
}