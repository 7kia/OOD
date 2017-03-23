#pragma once

#include "Shapes/Shapes.h"
#include <vector>
#include <memory>
#include <boost/range/algorithm/transform.hpp>

typedef std::function<bool(const std::shared_ptr<CShape> &, const std::shared_ptr<CShape> &)> ConditionSwap;

void		PrintListShapes(const ListDataShapes &listShapes, std::ostream &strm);

ListDataShapes GetSortedList(const ListDataShapes& listShapes,
							ConditionSwap conditionSwap);
