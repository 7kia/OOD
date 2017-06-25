#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(
		RectF const& frame = RectF(0, 0, 0, 0),
		IStylePtr const& fillStyle = nullptr,
		ILineStylePtr const& lineStyle = nullptr
	);

private:
	void DrawBehavior(ICanvas & canvas) const override;
};

