#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const sf::Color & fillColor, const sf::Color & outlineColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}


void CShape::SetFillColor(const sf::Color & color)
{
	m_fillColor = color;
}

sf::Color CShape::GetFillColor() const
{
	return m_fillColor;
}

void CShape::SetOutlineColor(const sf::Color & color)
{
	m_outlineColor = color;
}

sf::Color CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::ostream & operator<<(std::ostream & stream, sf::Vector2f const & vector)
{
	stream << "(" << vector.x << ", " << vector.x << ")";
	return stream;
}