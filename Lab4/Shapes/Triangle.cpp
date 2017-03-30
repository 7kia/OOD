#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(
	const sf::Vector2f firstPoint
	, const sf::Vector2f secondPoint
	, const sf::Vector2f thirdPoint
	, const sf::Color fillColor
	, const sf::Color outlineColor
)
	: CShape(fillColor, outlineColor)
	, m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
	, m_thirdPoint(thirdPoint)
{
}


void CTriangle::SetFirstPoint(const sf::Vector2f position)
{
	m_firstPoint = position;
}

void CTriangle::SetSecondPoint(const sf::Vector2f position)
{
	m_secondPoint = position;
}

void CTriangle::SetThirdPoint(const sf::Vector2f position)
{
	m_thirdPoint = position;
}

sf::Vector2f CTriangle::GetFirstPoint() const
{
	return m_firstPoint;
}

sf::Vector2f CTriangle::GetSecondPoint() const
{
	return m_secondPoint;
}

sf::Vector2f CTriangle::GetThirdPoint() const
{
	return m_thirdPoint;
}


void CTriangle::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

