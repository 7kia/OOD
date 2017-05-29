#include "stdafx.h"
#include "FillStyle.h"

CFillStyle::CFillStyle(bool enable, RGBAColor color)
	: m_isEnabled(enable)
	, m_color(color)
{

}

bool CFillStyle::IsEnabled() const
{
	return m_isEnabled;
}

void CFillStyle::Enable(bool enable)
{
	m_isEnabled = enable;
}

RGBAColor CFillStyle::GetColor() const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

