#pragma once
#include "..\modern_graphics_lib_pro\ModernGraphicsRenderer.h"
#include "..\graphics_lib_pro\ICanvas.h"

class CCanvasColoredObjectAdapter
	: public graphics_lib_pro::ICanvas
{
public:
	CCanvasColoredObjectAdapter(modern_graphics_lib_pro::CModernGraphicsRenderer & renderer);
	void SetColor(uint32_t rgbColor) override;
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib_pro::CModernGraphicsRenderer & m_renderer;
	modern_graphics_lib_pro::CPoint m_lastPoint;
	modern_graphics_lib_pro::CRGBAColor m_color;
};

