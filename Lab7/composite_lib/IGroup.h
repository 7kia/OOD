#pragma once
#include "IShape.h"

class IGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(std::shared_ptr<IShape> const& pShape, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
	virtual size_t GetShapesIndex(std::shared_ptr<IShape> const& pShape) = 0;
};