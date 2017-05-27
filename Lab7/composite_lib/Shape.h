#pragma once
#include "IShape.h"
#include "Style.h"
#include "LineStyle.h"
#include "CommonTypes.h"

class CShape : public IShape
{
public:
	CShape(
		RectD const& frame,
		IStylePtr const& fillStyle, 
		ILineStylePtr const& lineStyle
	);
public:
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;

	ILineStylePtr GetLineStyle()const override;
	void SetLineStyle(ILineStylePtr const& style) override;

	IStylePtr GetFillStyle()const override;
	void SetFillStyle(IStylePtr const& style) override;

	boost::optional<float> GetLineThickness() const override;
	void SetLineThickness(float thickness) override;

	std::shared_ptr<IGroup> GetGroup() override;

	void Draw(ICanvas & canvas) override;
protected:
	virtual void DrawBehavior(ICanvas & canvas) = 0;
private:
	IStylePtr m_pFillStyle;
	ILineStylePtr m_pLineStyle;
	RectD m_frame;

};

