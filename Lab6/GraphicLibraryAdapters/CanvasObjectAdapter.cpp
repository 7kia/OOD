#include "stdafx.h"
#include "CanvasObjectAdapter.h"

CCanvasObjectAdapter::CCanvasObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	: m_renderer(renderer)
	, m_lastPoint({ 0, 0 })
{
}

void CCanvasObjectAdapter::MoveTo(int x, int y)
{
	m_lastPoint = { x, y };
}

void CCanvasObjectAdapter::LineTo(int x, int y)
{
	m_renderer.BeginDraw();
	m_renderer.DrawLine(m_lastPoint, { x ,y });
	m_lastPoint = { x, y };
	m_renderer.EndDraw();
}
