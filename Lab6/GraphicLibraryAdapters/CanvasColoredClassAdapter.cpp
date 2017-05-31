#include "stdafx.h"
#include "CanvasColoredClassAdapter.h"

using namespace modern_graphics_lib_pro;

CCanvasColoredClassAdapter::CCanvasColoredClassAdapter(std::ostream & strm)
	: CModernGraphicsRenderer(strm)
	, m_color({ 0, 0, 0, 1 })
	, m_lastPoint({ 0,0 })
{

}

void CCanvasColoredClassAdapter::SetColor(uint32_t rgbColor)
{
	float r = ((rgbColor >> 16) & 0x0000FF) / 255.f;
	float g = ((rgbColor >> 8) & 0x0000FF) / 255.f;
	float b = (rgbColor & 0x0000FF) / 255.f;

	m_color = { r, g, b, 1.f };
}

void CCanvasColoredClassAdapter::MoveTo(int x, int y)
{
	m_lastPoint = { x, y };
}

void CCanvasColoredClassAdapter::LineTo(int x, int y)
{
	BeginDraw();
	DrawLine(m_lastPoint, { x, y }, m_color);
	m_lastPoint = { x, y };
	EndDraw();
}
