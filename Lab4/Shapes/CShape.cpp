#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const std::string & type, const sf::Color color)
	: m_type(type)
	, m_fillColor(color)
{
}


CShape::~CShape()
{
}

void CShape::SetFillColor(const sf::Color color)
{
	m_fillColor = color;
}

sf::Color CShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CShape::GetType() const
{
	return m_type;
}


std::ostream & operator<<(std::ostream & stream, sf::Vector2f const & vector)
{
	stream << "(" << vector.x << ", " << vector.x << ")";
	return stream;
}