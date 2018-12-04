/*
  ==============================================================================

    ButterworthFilter.h
    Created: 2 Dec 2018 1:43:37pm
    Author:  Family

  ==============================================================================
*/

#pragma once
#include "IIRFilterBase.h"

namespace homedsp
{
	class ButterworthFilter : public IIRFilterBase
	{
	private:
		void calculateLPF() override;
		void calculateHPF() override;
		void calculateBPF() override;
		void calculateBSF() override;
	};
}
