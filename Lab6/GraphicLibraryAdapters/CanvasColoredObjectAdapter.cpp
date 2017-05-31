#include "stdafx.h"
#include "CanvasColoredObjectAdapter.h"


CCanvasColoredObjectAdapter::CCanvasColoredObjectAdapter(modern_graphics_lib_pro::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
	, m_lastPoint({ 0, 0 })
	, m_color({ 0, 0, 0, 0 })
{
}

void CCanvasColoredObjectAdapter::SetColor(uint32_t rgbColor)
{
	float r = ((rgbColor >> 16) & 0x0000FF) / 255.f;
	float g = ((rgbColor >> 8) & 0x0000FF) / 255.f;
	float b = (rgbColor & 0x0000FF) / 255.f;

	m_color = { r, g, b, 1.f };
}

void CCanvasColoredObjectAdapter::MoveTo(int x, int y)
{
	m_lastPoint = { x, y };
}

void CCanvasColoredObjectAdapter::LineTo(int x, int y)
{
	m_renderer.BeginDraw();
	m_renderer.DrawLine(m_lastPoint, { x ,y }, m_color);
	m_lastPoint = { x, y };
	m_renderer.EndDraw();
}
