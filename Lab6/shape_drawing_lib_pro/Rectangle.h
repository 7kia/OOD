#pragma once
#include "ICanvasDrawable.h"
#include "Point.h"

namespace shape_drawing_lib_pro
{
	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point & leftTop, int width, int height, uint32_t color = 0x000000);
		void Draw(graphics_lib_pro::ICanvas & canvas)const override;
	private:
		Point m_leftTop;
		int m_width;
		int m_height;
		uint32_t m_color;
	};
}