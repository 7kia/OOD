#include "stdafx.h"
#include "Shape.h"


CShape::CShape(
	RectF const& frame,
	IStylePtr const& fillStyle,
	ILineStylePtr const& lineStyle
)
	: m_frame(frame)
	, m_pLineStyle(lineStyle)
	, m_pFillStyle(fillStyle)
{

}

RectF CShape::GetFrame() const
{
	return m_frame;
}

void CShape::SetFrame(const RectF & rect)
{
	m_frame = rect;
}

ILineStylePtr CShape::GetLineStyle() const
{
	return m_pLineStyle;
}

void CShape::SetLineStyle(ILineStylePtr const& style)
{
	m_pLineStyle = style;
}

IStylePtr CShape::GetFillStyle() const
{
	return m_pFillStyle;
}

void CShape::SetFillStyle(IStylePtr const& style)
{
	m_pFillStyle = style;
}

boost::optional<float> CShape::GetLineThickness() const
{
	return m_pLineStyle->GetLineThikness();
}

void CShape::SetLineThickness(float thickness)
{
	m_pLineStyle->SetLineThikness(thickness);
}

std::shared_ptr<IGroup> CShape::GetGroup()
{
	return nullptr;
}

void CShape::Draw(ICanvas & canvas) const
{
	bool isFillStyleEnabled = m_pFillStyle && m_pFillStyle->IsEnabled();

	if (isFillStyleEnabled)
	{
		canvas.BeginFill(m_pFillStyle->GetColor());
	}

	if (m_pLineStyle->IsEnabled())
	{
		canvas.SetLineColor(m_pLineStyle->GetColor());
	}
	else
	{
		canvas.SetLineColor(0x00000000);
	}
	canvas.SetLineThickness(m_pLineStyle->GetLineThikness());
	DrawBehavior(canvas);

	if (isFillStyleEnabled)
	{
		canvas.EndFill();
	}
}

