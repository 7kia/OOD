#pragma once

#include "CShape.h"

class CRectangle final :// was exported from lab 3 Rectangle
	public CShape
{
public:
	CRectangle() = default;
	CRectangle(
		const sf::Vector2f & leftTopPoint
		, const SSize & size
		, const sf::Color & fillColor
		, const sf::Color & outlineColor
	);
public:

	void				SetLeftTopPoint(const sf::Vector2f leftTopPoint);
	sf::Vector2f		GetLeftTopPoint() const;

	void				SetSize(const SSize size);
	SSize				GetSize() const;
private:

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_leftTopPoint;
	SSize				m_size;
};