#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(
		RectD const& frame,
		IStylePtr const& fillStyle,
		ILineStylePtr const& lineStyle
	);
private:
	void DrawBehavior(ICanvas & canvas) override;
};

