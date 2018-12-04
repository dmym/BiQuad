/*
  ==============================================================================

    LinkwitzRileyFilter.h
    Created: 2 Dec 2018 1:43:53pm
    Author:  Family

  ==============================================================================
*/

#pragma once
#include "IIRFilterBase.h"

namespace homedsp
{
	class LinkwitzRileyFilter : public IIRFilterBase
	{
	private:
		void calculateLPF() override;
		void calculateHPF() override;
		void calculateBPF() {};
		void calculateBSF() {};
	};
}