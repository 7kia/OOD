#pragma once
#include "IShape.h"

class CSlide
{
public:
	void AddShape(std::shared_ptr<IShape> const& pShape);
	void RemoveShape(size_t index);
	void Draw(ICanvas & canvas) const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

