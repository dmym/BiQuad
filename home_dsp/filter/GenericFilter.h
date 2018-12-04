/*
  ==============================================================================

	GenericFilter.h
	Created: 2 Dec 2018 1:41:26pm
	Author:  Family

  ==============================================================================
*/

#pragma once
#include "IIRFilterBase.h"

namespace homedsp
{
	class GenericFilter : public IIRFilterBase
	{
	private:
		void calculateLPF() override;
		void calculateHPF() override;
		void calculateBPF() override;
		void calculateBSF() override;
	};
}

