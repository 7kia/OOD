#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment()
	: CShape("Line", DEFAULT_COLOR)
{
}


CLineSegment::CLineSegment(
	const sf::Vector2f firstPoint
	, const sf::Vector2f secondPoint
	, const sf::Color color
)
	: CShape("Line", color)
	, m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
{
}

CLineSegment::~CLineSegment()
{
}

float CLineSegment::GetPerimeter() const
{
	
	return sqrtf(std::powf((m_firstPoint.x - m_secondPoint.x), 2.f)
					+
				std::powf((m_firstPoint.y - m_secondPoint.y), 2.f));
}

float CLineSegment::GetArea() const
{
	return 0.0f;
}

std::string CLineSegment::GetStringPresentation() const
{
	std::ostringstream strm;
	strm << std::setprecision(3);

	CShape::AppendProperties(strm);
	CLineSegment::AppendProperties(strm);

	return strm.str();
}

void CLineSegment::SetPositionFirstPoint(sf::Vector2f position)
{
	m_firstPoint = position;
}

void CLineSegment::SetPositionFirstPoint(float x, float y)
{
	m_firstPoint = sf::Vector2f(x, y);
}

sf::Vector2f CLineSegment::GetFirstPoint() const
{
	return m_firstPoint;
}

void CLineSegment::SetPositionSecondPoint(sf::Vector2f position)
{
	m_secondPoint = position;
}

void CLineSegment::SetPositionSecondPoint(float x, float y)
{
	m_secondPoint = sf::Vector2f(x, y);
}

sf::Vector2f CLineSegment::GetSecondPoint() const
{
	return m_secondPoint;
}

void CLineSegment::AppendProperties(std::ostream & strm) const
{
	strm << "\tPosition first point = (" << m_firstPoint.x << ", "
										<< m_firstPoint.y << ")" << std::endl
		<< "\tPosition second point = (" << m_secondPoint.x << ", " 
										<< m_secondPoint.y << ")" << std::endl;
}

void CLineSegment::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}