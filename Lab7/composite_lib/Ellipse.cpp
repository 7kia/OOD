#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(
	RectD const& frame,
	IStylePtr const& fillStyle,
	ILineStylePtr const& lineStyle
)
	: CShape(frame, fillStyle, lineStyle)
{

}

void CEllipse::DrawBehavior(ICanvas & canvas)
{
	auto frame = GetFrame();
	canvas.DrawEllipse(frame.left, frame.top, frame.width, frame.height);
}
