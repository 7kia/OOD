#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(
		RectD const& frame,
		IStylePtr const& fillStyle,
		ILineStylePtr const& lineStyle
	);

private:
	void DrawBehavior(ICanvas & canvas) override;
};

