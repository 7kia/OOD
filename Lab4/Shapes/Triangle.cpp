#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle()
	: CSolidShape("Triangle", DEFAULT_COLOR, DEFAULT_COLOR)
{
}

CTriangle::CTriangle(
	const sf::Vector2f firstPoint
	, const sf::Vector2f secondPoint
	, const sf::Vector2f thirdPoint
	, const sf::Color fillColor
	, const sf::Color outlineColor
)
	: CSolidShape("Triangle", fillColor, outlineColor)
	, m_firstLine(firstPoint, secondPoint, outlineColor)
	, m_secondLine(secondPoint, thirdPoint, outlineColor)
	, m_thirdLine(thirdPoint, firstPoint, outlineColor)
{
}


CTriangle::~CTriangle()
{
}

float CTriangle::GetPerimeter() const
{
	return m_firstLine.GetPerimeter() + m_secondLine.GetPerimeter() + m_thirdLine.GetPerimeter();
}

float CTriangle::GetArea() const
{
	float halfPerimeter = GetPerimeter() / 2.f;
	float lengthFirtsLine = m_firstLine.GetPerimeter();
	float lengthSecondLine = m_secondLine.GetPerimeter();
	float lengthThirdLine = m_thirdLine.GetPerimeter();

	return sqrtf(halfPerimeter * (halfPerimeter - lengthFirtsLine)
								* (halfPerimeter - lengthSecondLine)
								* (halfPerimeter - lengthThirdLine));
}


void CTriangle::SetPositionFirstPoint(sf::Vector2f position)
{
	m_firstLine.SetPositionFirstPoint(position);
	m_thirdLine.SetPositionSecondPoint(position);
}

void CTriangle::SetPositionFirstPoint(float x, float y)
{
	m_firstLine.SetPositionFirstPoint(x, y);
	m_thirdLine.SetPositionSecondPoint(x, y);
}

void CTriangle::SetPositionSecondPoint(sf::Vector2f position)
{
	m_firstLine.SetPositionSecondPoint(position);
	m_secondLine.SetPositionFirstPoint(position);

}

void CTriangle::SetPositionSecondPoint(float x, float y)
{
	m_firstLine.SetPositionSecondPoint(x, y);
	m_secondLine.SetPositionFirstPoint(x, y);
}

void CTriangle::SetPositionThirdPoint(sf::Vector2f position)
{
	m_secondLine.SetPositionSecondPoint(position);
	m_thirdLine.SetPositionFirstPoint(position);
}

void CTriangle::SetPositionThirdPoint(float x, float y)
{
	m_secondLine.SetPositionSecondPoint(x, y);
	m_thirdLine.SetPositionFirstPoint(x, y);
}

sf::Vector2f CTriangle::GetFirstPoint() const
{
	return m_firstLine.GetFirstPoint();
}

sf::Vector2f CTriangle::GetSecondPoint() const
{
	return m_firstLine.GetSecondPoint();
}

sf::Vector2f CTriangle::GetThirdPoint() const
{
	return m_secondLine.GetSecondPoint();
}


void CTriangle::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

