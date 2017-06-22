#pragma once
#include "CommonTypes.h"
#include "IStyle.h"
#include "ILineStyle.h"
#include "ICanvas.h"
#include <boost\optional\optional.hpp>
#include <memory>

class IGroup;

class IShape
{
public:
	virtual ~IShape() = default;

	virtual ILineStylePtr GetLineStyle() const = 0;
	virtual void SetLineStyle(ILineStylePtr const& style) = 0;

	virtual IStylePtr GetFillStyle() const = 0;
	virtual void SetFillStyle(IStylePtr const& style) = 0;

	virtual boost::optional<float> GetLineThickness() const = 0;
	virtual void SetLineThickness(float thickness) = 0;

	virtual RectF GetFrame() const = 0;
	virtual void SetFrame(const RectF & rect) = 0;

	virtual void Draw(ICanvas & canvas) const = 0;

	virtual std::shared_ptr<IGroup> GetGroup() = 0;
};