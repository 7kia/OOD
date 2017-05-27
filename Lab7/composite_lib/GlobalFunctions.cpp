#include "stdafx.h"
#include "GlobalFunctions.h"

void CheckIndex(size_t index, size_t max)
{
	if (index > max)
	{
		throw std::out_of_range("Index out range");
	}
};
