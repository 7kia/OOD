#pragma once
#include "..\modern_graphics_lib_pro\ModernGraphicsRenderer.h"
#include "..\graphics_lib_pro\ICanvas.h"

class CCanvasColoredAdapter 
	: public graphics_lib_pro::ICanvas
	, public modern_graphics_lib_pro::CModernGraphicsRenderer
{
public:
	CCanvasColoredAdapter(std::ostream & strm);
	void SetColor(uint32_t rgbColor) override;
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib_pro::CRGBAColor m_color;
	modern_graphics_lib_pro::CPoint m_lastPoint;
};

