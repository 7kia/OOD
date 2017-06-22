#pragma once

#include "IGroup.h"

#include <vector>
#include <memory>

class CGroup 
	: public IGroup
	, public std::enable_shared_from_this<IGroup>
{
public:
	//--------------------------------------------
	// IShape
	ILineStylePtr GetLineStyle() const override;
	void SetLineStyle(ILineStylePtr const& style) override;

	IStylePtr GetFillStyle() const override;
	void SetFillStyle(IStylePtr const& style) override;

	boost::optional<float> GetLineThickness() const override;
	void SetLineThickness(float thickness) override;

	void Draw(ICanvas & canvas) const override final;

	std::shared_ptr<IGroup> GetGroup() override;

	RectF GetFrame() const override;
	void SetFrame(const RectF & rect) override;
	//--------------------------------------------
	// IGroup
	size_t GetShapesCount() const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void InsertShape(std::shared_ptr<IShape> const& pShape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;
	size_t GetShapesIndex(std::shared_ptr<IShape> const& pShape) override;
	//--------------------------------------------
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

