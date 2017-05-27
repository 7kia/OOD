#pragma once
#include "IShape.h"

class IGroup : public IShape
{
	virtual size_t GetShapesCount() const = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(std::shared_ptr<IShape> const& pShape, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
};