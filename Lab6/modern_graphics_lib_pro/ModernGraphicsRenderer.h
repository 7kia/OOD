#pragma once

#include <iosfwd>

#include "Point.h"
#include "RBGAColor.h"

namespace modern_graphics_lib_pro
{

class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream & strm);
	~CModernGraphicsRenderer();
public:

	void BeginDraw();

	void DrawLine(
		const CPoint & start,
		const CPoint & end,
		const CRGBAColor& color
	);
	void EndDraw();
private:
	std::ostream & m_out;
	bool m_drawing = false;
};


}