#pragma once
#include "..\graphics_lib\ICanvas.h"
#include "..\modern_graphics_lib\ModernGraphicsRenderer.h"

class CCanvasClassAdapter 
	: public graphics_lib::ICanvas
	, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CCanvasClassAdapter(std::ostream & strm);
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib::CPoint m_lastPoint;
};

