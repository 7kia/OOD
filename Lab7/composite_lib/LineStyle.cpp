#include "stdafx.h"
#include "LineStyle.h"

CLineStyle::CLineStyle(
	bool enable,
	RGBAColor color,
	float thikness
) 
	: m_isEnabled(enable)
	, m_color(color)
	, m_lineThikness(thikness)
{
}

bool CLineStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CLineStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

RGBAColor CLineStyle::GetColor() const
{
	return m_color;
}

void CLineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

float CLineStyle::GetLineThikness() const
{
	return m_lineThikness;
}

void CLineStyle::SetLineThikness(float thikness)
{
	m_lineThikness = thikness;
}