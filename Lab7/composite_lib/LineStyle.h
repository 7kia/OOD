#pragma once
#include "ILineStyle.h"

class CLineStyle : public ILineStyle
{
public:
	CLineStyle(
		bool enable,
		RGBAColor color,
		float thikness
	);
public:
	bool IsEnabled() const override final;
	void Enable(bool enable) override final;

	RGBAColor GetColor() const override final;
	void SetColor(RGBAColor color) override final;

	float GetLineThikness() const override final;
	void SetLineThikness(float thikness) override final;

private:
	float m_lineThikness = 1.f;
	bool m_isEnabled = false;
	RGBAColor m_color;
};