#pragma once
#include "Shape.h" 
#include "CommonTypes.h"

class CRectangle : public CShape
{
public:
	CRectangle(
		RectF const& frame,
		IStylePtr const& fillStyle, 
		ILineStylePtr const& lineStyle
	);
private:
	void DrawBehavior(ICanvas & canvas) const override;
};

