#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(
		RectF const& frame,
		IStylePtr const& fillStyle,
		ILineStylePtr const& lineStyle
	);
private:
	void DrawBehavior(ICanvas & canvas) override;
};

