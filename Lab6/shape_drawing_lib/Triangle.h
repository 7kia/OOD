#pragma once
#include "ICanvasDrawable.h"
#include "Point.h"

namespace shape_drawing_lib
{

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3);
	void Draw(graphics_lib::ICanvas & canvas)const override;
private:
	Point m_point1;
	Point m_point2;
	Point m_point3;
};

}