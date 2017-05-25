#include "stdafx.h"
#include "HarmonicStringGenerator.h"
#include <sstream>
#include <boost\format.hpp>

std::wstring CHarmonicStringGenerator::CreateHarmonicString(
	float amplitude,
	FunctionType const& function,
	float frequency,
	float phase
)
{
	auto ToSignedString = [](double value) {
		std::wostringstream strm;
		strm << std::abs(value);

		return ((value < 0) ? L"- " : L"+ ") + strm.str();
	};

	std::map<FunctionType, std::wstring> functions = {
		{ FunctionType::Sin, L"sin" },
		{ FunctionType::Cos, L"cos" },
	};

	std::wostringstream strm;
	strm << amplitude << L"*" << functions.at(function) << L"(";
	if (frequency != 1)
	{
		strm << frequency << L"*x";
	}
	else
	{
		strm << L"x";
	}
	strm << (phase != 0 ? ToSignedString(phase) : L"") << L")";
	return strm.str();
}
