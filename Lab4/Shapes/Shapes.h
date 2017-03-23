#pragma once

#include "IShape.h"
#include "ISolidShape.h"
#include "Circle.h"
#include "LineSegment.h"
#include "MyCPoint.h"
#include "Rectangle.h"
#include "Triangle.h"

#include <vector>

typedef std::shared_ptr<CShape> CShapePtr;
typedef std::vector<CShapePtr> ListDataShapes;

