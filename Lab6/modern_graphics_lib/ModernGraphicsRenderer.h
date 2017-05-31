#pragma once
#include <iosfwd>
#include "Point.h"


namespace modern_graphics_lib
{
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm);
		~CModernGraphicsRenderer();

		void BeginDraw();
		void DrawLine(const CPoint & start, const CPoint & end);
		void EndDraw();

	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}