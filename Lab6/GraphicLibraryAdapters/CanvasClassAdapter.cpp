#include "stdafx.h"
#include "CanvasClassAdapter.h"

using namespace modern_graphics_lib;

CCanvasClassAdapter::CCanvasClassAdapter(std::ostream & strm)
	: modern_graphics_lib::CModernGraphicsRenderer(strm)
	, m_lastPoint({ 0 ,0 })
{

}

void CCanvasClassAdapter::MoveTo(int x, int y)
{
	m_lastPoint = { x, y };
}

void CCanvasClassAdapter::LineTo(int x, int y)
{
	BeginDraw();
	DrawLine(m_lastPoint, { x, y });
	m_lastPoint = { x, y };
	EndDraw();
}