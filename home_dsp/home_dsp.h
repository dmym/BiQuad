/*******************************************************************************

BEGIN_JUCE_MODULE_DECLARATION

ID:			 home_dsp
vendor:		 home
version:	 1.0
name:		 DSP
description: Basic DSP algorithms

END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#define HOME_DSP_H_INCLUDED

#include <juce_core/juce_core.h>

#include "filter/IIRFilterBase.h"
#include "filter/GenericFilter.h"
#include "filter/ButterworthFilter.h"
#include "filter/LinkwitzRileyFilter.h"
#include "filter/IIRFilters.h"

