#include "stdafx.h"
#include "Rectangle.h"

namespace shape_drawing_lib_pro
{

CRectangle::CRectangle(const Point & leftTop, int width, int height, uint32_t color /*= 0x000000*/)
	: m_color(color)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{

}

void CRectangle::Draw(graphics_lib_pro::ICanvas & canvas) const
{
	canvas.SetColor(m_color);
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
}

}