#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(
	const sf::Vector2f & leftTopPoint
	, const SSize & size
	, const sf::Color & fillColor
	, const sf::Color & outlineColor
)
	: CShape(fillColor, outlineColor)
	, m_leftTopPoint(leftTopPoint)
	, m_size(size)
{
}

void CRectangle::SetLeftTopPoint(const sf::Vector2f & leftTopPoint)
{
	m_leftTopPoint = leftTopPoint;
}

sf::Vector2f CRectangle::GetLeftTopPoint() const
{
	return m_leftTopPoint;
}

void CRectangle::SetSize(const SSize & size)
{
	m_size = size;
}

SSize CRectangle::GetSize() const
{
	return m_size;
}


void CRectangle::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}
