#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(
		RectF const& frame = RectF(0, 0, 0, 0),
		IStylePtr const& fillStyle = nullptr,
		ILineStylePtr const& lineStyle = nullptr
	);
private:
	void DrawBehavior(ICanvas & canvas) const override;
};

