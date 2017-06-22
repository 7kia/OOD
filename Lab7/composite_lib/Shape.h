#pragma once
#include "IShape.h"
#include "FillStyle.h"
#include "LineStyle.h"
#include "CommonTypes.h"

class CShape : public IShape
{
public:
	CShape(
		RectF const& frame,
		IStylePtr const& fillStyle, 
		ILineStylePtr const& lineStyle
	);
public:
	RectF GetFrame() const override;
	void SetFrame(const RectF & rect) override;

	ILineStylePtr GetLineStyle() const override;
	void SetLineStyle(ILineStylePtr const& style) override;

	IStylePtr GetFillStyle() const override;
	void SetFillStyle(IStylePtr const& style) override;

	boost::optional<float> GetLineThickness() const override;
	void SetLineThickness(float thickness) override;

	std::shared_ptr<IGroup> GetGroup() override;

	void Draw(ICanvas & canvas) const override final;
protected:
	virtual void DrawBehavior(ICanvas & canvas) const = 0;
private:
	IStylePtr m_pFillStyle;
	ILineStylePtr m_pLineStyle;
	RectF m_frame;
};

