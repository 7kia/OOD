#include "stdafx.h"
#include "Triangle.h"

namespace shape_drawing_lib_pro
{




CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3, uint32_t color /*= 0x000000*/)
	: m_point1(p1)
	, m_point2(p2)
	, m_point3(p3)
	, m_color(color)
{

}

void CTriangle::Draw(graphics_lib_pro::ICanvas & canvas) const
{
	canvas.SetColor(m_color);

	canvas.MoveTo(m_point1.x, m_point1.y);
	canvas.LineTo(m_point2.x, m_point2.y);
	canvas.LineTo(m_point3.x, m_point3.y);
	canvas.LineTo(m_point1.x, m_point1.y);
}

}