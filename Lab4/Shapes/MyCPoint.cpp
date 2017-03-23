#include "stdafx.h"
#include "MyCPoint.h"



MyCPoint::MyCPoint()
	: CShape("Point", DEFAULT_COLOR)
{
}


MyCPoint::MyCPoint(sf::Vector2f position, SColor color)
	: CShape("Point", color)
	, m_position(position)
{
}


MyCPoint::~MyCPoint()
{
}


float MyCPoint::GetPerimeter() const
{
	return 0;
}

float MyCPoint::GetArea() const
{
	return 0;
}

std::string MyCPoint::GetStringPresentation() const
{
	std::ostringstream strm;
	strm << std::setprecision(3);

	CShape::AppendProperties(strm);
	MyCPoint::AppendProperties(strm);

	return strm.str();
}

void MyCPoint::SetPosition(sf::Vector2f position)
{
	m_position = position;
}

void MyCPoint::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}

sf::Vector2f MyCPoint::GetPosition() const
{
	return m_position;
}

void MyCPoint::AppendProperties(std::ostream & strm) const
{
	strm << "\tPosition = (" << m_position.x << ", " << m_position.y << ")" << std::endl;
}

void MyCPoint::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

