#include "stdafx.h"
#include "Triangle.h"


namespace shape_drawing_lib
{
	CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3)
		: m_point1(p1)
		, m_point2(p2)
		, m_point3(p3)
	{
	}

	void CTriangle::Draw(graphics_lib::ICanvas & canvas) const
	{
		canvas.MoveTo(m_point1.x, m_point1.y);
		canvas.LineTo(m_point2.x, m_point2.y);
		canvas.LineTo(m_point3.x, m_point3.y);
		canvas.LineTo(m_point1.x, m_point1.y);
	}
}