#include "stdafx.h"
#include "MyCPoint.h"



CMyPoint::CMyPoint()
	: CShape("Point", DEFAULT_COLOR)
{
}


CMyPoint::CMyPoint(sf::Vector2f position, const sf::Color color)
	: CShape("Point", color)
	, m_position(position)
{
}


CMyPoint::~CMyPoint()
{
}


float CMyPoint::GetPerimeter() const
{
	return 0;
}

float CMyPoint::GetArea() const
{
	return 0;
}


void CMyPoint::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

void CMyPoint::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}

sf::Vector2f CMyPoint::GetPosition() const
{
	return m_position;
}


void CMyPoint::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

