#include "stdafx.h"
#include "CSolidShape.h"


CSolidShape::CSolidShape(
	const std::string & type
	, const sf::Color fillColor
	, const sf::Color boundColor
)
	: CShape(type, fillColor)
	, m_outlineColor(boundColor)
{
}

CSolidShape::~CSolidShape()
{
}


void CSolidShape::SetOutlineColor(const sf::Color color)
{
	m_outlineColor = color;
}

sf::Color CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}


