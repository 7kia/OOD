#include "stdafx.h"
#include "CSolidShape.h"


CSolidShape::CSolidShape(const std::string & type, SColor fillColor, SColor boundColor)
	: CShape(type, fillColor)
	, m_outlineColor(boundColor)
{
}

CSolidShape::~CSolidShape()
{
}


void CSolidShape::SetOutlineColor(uint8_t r, uint8_t g, uint8_t b)
{
	m_outlineColor.red = r;
	m_outlineColor.green = g;
	m_outlineColor.blue = b;
}

void CSolidShape::SetOutlineColor(SColor color)
{
	m_outlineColor = color;
}

SColor CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CSolidShape::AppendProperties(std::ostream & strm) const
{
	CShape::AppendProperties(strm);
	strm << "\tOutline color = " << GetOutlineColor() << std::endl;
}

