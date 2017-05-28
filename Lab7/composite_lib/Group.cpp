#include "stdafx.h"

#include "GlobalFunctions.h"
#include "Group.h"

#include <algorithm>
#include <boost\limits.hpp>

RectD CGroup::GetFrame()
{
	if (GetShapesCount() == 0)
	{
		return RectD(0, 0, 0, 0);
	}

	RectD frame = {
		std::numeric_limits<double>::infinity(), 
		std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity(),
		-std::numeric_limits<double>::infinity()
	};
	double maxRight = 0.;
	double maxBottom = 0.;
	for (auto & shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		frame.left = std::min(shapeFrame.left, frame.left);
		frame.top = std::min(shapeFrame.top, frame.top);
		maxRight = std::max(shapeFrame.width + shapeFrame.left, maxRight);
		maxBottom = std::max(shapeFrame.height + shapeFrame.top, maxBottom);
	}
	frame.width = maxRight - frame.left;
	frame.height = maxBottom - frame.top;

	return frame;
}

void CGroup::SetFrame(const RectD & rect)
{
	if (GetShapesCount() != 0)
	{
		auto oldFrame = GetFrame();

		double ratioX = rect.width / oldFrame.width;
		double ratioY = rect.height / oldFrame.height;

		for (auto & shape : m_shapes)
		{
			auto shapeFrame = shape->GetFrame();
			double paddingX = shapeFrame.left - oldFrame.left;
			double paddingY = shapeFrame.top - oldFrame.top;

			shapeFrame.left = rect.left + paddingX * ratioX;
			shapeFrame.top = rect.top + paddingY * ratioY;
			shapeFrame.width *= ratioX;
			shapeFrame.height *= ratioY;

			shape->SetFrame(shapeFrame);
		}
	}
}

ILineStylePtr CGroup::GetLineStyle() const
{
	ILineStylePtr lineStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto & shape) {
			return (shape->GetLineStyle() == m_shapes.front()->GetLineStyle());
		});
		lineStyle = stylesEqual ? m_shapes.front()->GetLineStyle() : nullptr;
	}
	return lineStyle;
}

void CGroup::SetLineStyle(ILineStylePtr const& style)
{
	for(auto & shape : m_shapes) {
		shape->SetLineStyle(style);
	}
}

IStylePtr CGroup::GetFillStyle() const
{
	IStylePtr fillStyle;
	if (!m_shapes.empty())
	{
		bool stylesEqual = std::all_of(m_shapes.cbegin(), m_shapes.cend(), [&](auto & shape) {
			return (shape->GetFillStyle() == m_shapes.front()->GetFillStyle());
		});
		fillStyle = stylesEqual ? m_shapes.front()->GetFillStyle() : nullptr;
	}
	return fillStyle;
}

void CGroup::SetFillStyle(IStylePtr const& style)
{
	for(auto & shape : m_shapes) {
		shape->SetFillStyle(style);
	}
}

boost::optional<float> CGroup::GetLineThickness() const
{
	boost::optional<float> thickness;
	if (!m_shapes.empty())
	{
		bool thicknessesEqual = std::all_of(m_shapes.begin(), m_shapes.end(),
			[&](std::shared_ptr<IShape> const& shape) 
			{
			return shape->GetLineThickness() 
				&& m_shapes.front()->GetLineThickness() 
				&& (shape->GetLineThickness().get() == m_shapes.front()->GetLineThickness().get());
			}
		);
		thickness = thicknessesEqual ? m_shapes.front()->GetLineThickness() : boost::none;
	}
	return thickness;
}

void CGroup::SetLineThickness(float thickness)
{
	for(auto & shape : m_shapes) {
		shape->SetLineThickness(thickness);
	}
}

void CGroup::Draw(ICanvas & canvas)
{
	for(auto & shape : m_shapes) {
		shape->Draw(canvas);
	}
}

std::shared_ptr<IGroup> CGroup::GetGroup()
{
	return shared_from_this();
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(size_t index)
{
	CheckIndex(index, m_shapes.size());
	return m_shapes[index];
}

void CGroup::InsertShape(std::shared_ptr<IShape> const& pShape, size_t index)
{
	// TODO : check correctness insert and remove for this(+) and group
	CheckIndex(index, m_shapes.size());
	if (pShape.get() != this)
	{
		m_shapes.insert(m_shapes.begin() + index, pShape);
	}
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	CheckIndex(index, m_shapes.size() + 1);
	m_shapes.erase(m_shapes.begin() + index);
}
