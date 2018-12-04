/*
  ==============================================================================

    IIRFilterBase.h
    Created: 2 Dec 2018 1:37:38pm
    Author:  Family

  ==============================================================================
*/

#pragma once
namespace homedsp
{
	struct ChannelFeed
	{
		ChannelFeed() :
			xn_1(0.0f),
			xn_2(0.0f),
			yn_1(0.0f),
			yn_2(0.0f)
		{
		}

		float xn_1;
		float xn_2;
		float yn_1;
		float yn_2;
	};

	enum IIRType
	{
		LPF,
		HPF,
		BPF,
		BSF
	};

	enum IIRDesign
	{
		Generic,
		Butterworth,
		LinkwitzRiley
	};

	class IIRFilterBase
	{
	public:

		void updateFilterCoefficients(float cutoff, float q, float sampleRate, IIRType filterType);
		float applyFiltering(float xn, ChannelFeed& channel);

	protected:

		// filter parameters
		float cutoff;
		float q;
		float sampleRate;

		// equation coefficients
		float a0;
		float a1;
		float a2;
		float b1;
		float b2;

		virtual void calculateLPF() = 0;
		virtual void calculateHPF() = 0;
		virtual void calculateBPF() = 0;
		virtual void calculateBSF() = 0;
	};
}