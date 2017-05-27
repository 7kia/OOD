#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(
	RectD const& frame,
	IStylePtr const& fillStyle,
	ILineStylePtr const& lineStyle
)
	: CShape(frame, fillStyle, lineStyle)
{

}

void CTriangle::DrawBehavior(ICanvas & canvas)
{
	auto frame = GetFrame();
	canvas.MoveTo(frame.left, frame.top + frame.height);
	canvas.LineTo(frame.left + (frame.width / 2.f), frame.top);
	canvas.LineTo(frame.left + frame.width, frame.top + frame.height);
	canvas.LineTo(frame.left, frame.top + frame.height);
}
