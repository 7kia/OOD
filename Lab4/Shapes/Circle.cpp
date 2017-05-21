#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle(
	const sf::Vector2f & center
	, const float radius
	, const sf::Color & fillColor
	, const sf::Color & outlineColor
)
	: CShape(fillColor, outlineColor)
	, m_positionCenter(center)
	, m_radius(radius)
{
}


void CCircle::SetRadius(float radius)
{
	if (radius < 0.f)
	{
		m_radius = 0;
	}
	else
	{
		m_radius = radius;
	}
}

float CCircle::GetRadius() const
{
	return m_radius;
}


void CCircle::SetPosition(const sf::Vector2f & position)
{
	m_positionCenter = position;
}

sf::Vector2f CCircle::GetPosition() const
{
	return m_positionCenter;
}


void CCircle::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}
