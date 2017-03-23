#include "stdafx.h"
#include "Circle.h"



CCircle::CCircle()
	: CSolidShape("Circle", DEFAULT_COLOR, DEFAULT_COLOR)
{
}

CCircle::CCircle(
	const sf::Vector2f center
	, float radius
	, const sf::Color fillColor
	, const sf::Color outlineColor
)
	: CSolidShape("Circle", fillColor, outlineColor)
	, m_positionCenter(center)
	, m_radius(radius)
{
}


CCircle::~CCircle()
{
}

float CCircle::GetPerimeter() const
{
	return pi * 2.f * m_radius;
}

float CCircle::GetArea() const
{
	return pi * m_radius * m_radius;
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

void CCircle::SetPositionCenter(float x, float y)
{
	m_positionCenter = { x, y };
}

void CCircle::SetPositionCenter(sf::Vector2f position)
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
