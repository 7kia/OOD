#include "stdafx.h"
#include "SorterShapes.h"

void PrintListShapes(const ListDataShapes& listShapes, std::ostream &strm)
{
	for (const auto& shape : listShapes)
	{
		strm << shape->GetStringPresentation();
	}
}

ListDataShapes GetSortedList(const ListDataShapes& listShapes,
							ConditionSwap conditionSwap)
{

	ListDataShapes sortedList = listShapes;

	std::sort(sortedList.begin(), sortedList.end(), conditionSwap);

	return sortedList;
}
