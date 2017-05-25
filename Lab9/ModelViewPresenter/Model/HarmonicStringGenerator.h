#pragma once
#include "FunctionType.h"
#include <string>

class CHarmonicStringGenerator
{
public:
	static std::wstring CreateHarmonicString(
		float amplitude,
		FunctionType const& function,
		float frequency,
		float phase
	);
};