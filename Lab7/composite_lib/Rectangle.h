#pragma once
#include "Shape.h" 
#include "CommonTypes.h"

class CRectangle : public CShape
{
public:
	CRectangle(
		RectF const& frame = RectF(0,0,0,0),
		IStylePtr const& fillStyle = nullptr, 
		ILineStylePtr const& lineStyle = nullptr
	);
private:
	void DrawBehavior(ICanvas & canvas) const override;
};

