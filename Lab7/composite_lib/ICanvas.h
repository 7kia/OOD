#pragma once
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetLineThickness(float thickness) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void MoveTo(float x, float y) = 0;
	virtual void LineTo(float x, float y) = 0;
	virtual void DrawEllipse(
		float left,
		float top,
		float width,
		float height
	) = 0;
};