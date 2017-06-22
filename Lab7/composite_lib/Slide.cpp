#include "stdafx.h"
#include "GlobalFunctions.h"
#include "Slide.h"


void CSlide::AddShape(std::shared_ptr<IShape> const& pShape)
{
	m_shapes.push_back(pShape);
}

void CSlide::RemoveShape(size_t index)
{
	CheckIndex(index, m_shapes.size() + 1);
	m_shapes.erase(m_shapes.begin() + index);
}

void CSlide::Draw(ICanvas & canvas) const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
