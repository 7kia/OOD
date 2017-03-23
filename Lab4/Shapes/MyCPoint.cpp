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

std::string CMyPoint::GetStringPresentation() const
{
	std::ostringstream strm;
	strm << std::setprecision(3);

	CShape::AppendProperties(strm);
	CMyPoint::AppendProperties(strm);

	return strm.str();
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

void CMyPoint::AppendProperties(std::ostream & strm) const
{
	strm << "\tPosition = (" << m_position.x << ", " << m_position.y << ")" << std::endl;
}

void CMyPoint::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

