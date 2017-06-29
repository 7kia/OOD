#pragma once
#include "FunctionType.h"
#include <string>

namespace HarmonicStringGenerator
{
	std::wstring CreateHarmonicString(
		float amplitude,
		FunctionType function,
		float frequency,
		float phase
	);
}