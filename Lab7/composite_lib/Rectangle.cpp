#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(
	RectF const& frame,
	IStylePtr const& fillStyle,
	ILineStylePtr const& lineStyle
)
	: CShape(frame, fillStyle, lineStyle)
{

}

void CRectangle::DrawBehavior(ICanvas & canvas)
{
	auto frame = GetFrame();
	canvas.MoveTo(frame.left, frame.top);
	canvas.LineTo(frame.left + frame.width, frame.top);
	canvas.LineTo(frame.left + frame.width, frame.top + frame.height);
	canvas.LineTo(frame.left, frame.top + frame.height);
	canvas.LineTo(frame.left, frame.top);
}

