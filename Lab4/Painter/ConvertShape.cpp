#include "stdafx.h"
#include "ConvertShape.h"

ListRenderShapes ConvertDataShapesToRenderShapes(const ListDataShapes & data)
{
	ListRenderShapes result;
	CShapeVisitor visitor;
	for (const auto& shape : data)
	{
		shape->Accept(visitor);
		result.push_back(visitor.GetAcceptShape());
	}
	return result;
}