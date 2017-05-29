#pragma once
#include "IStyle.h"

class CFillStyle :	public IStyle
{
public:
	CFillStyle(bool enable, RGBAColor color);
public:

	bool IsEnabled() const override final;
	void Enable(bool enable) override final;

	RGBAColor GetColor() const override final;
	void SetColor(RGBAColor color) override final;

protected:
	bool m_isEnabled = false;
	RGBAColor m_color;
};

bool operator==(IStylePtr const& first, IStylePtr const& second);