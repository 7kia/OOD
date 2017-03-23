#include "stdafx.h"
#include "Rectangle.h"

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

CRectangle::CRectangle()
	: CSolidShape("Rectangle", DEFAULT_COLOR, DEFAULT_COLOR)
	, m_width(0)
	, m_height(0)
{
}

CRectangle::CRectangle(
	const sf::Vector2f leftTopPoint
	, float width
	, float height
	, const sf::Color fillColor
	, const sf::Color outlineColor
)
	: CSolidShape("Rectangle", fillColor, outlineColor)
	, m_leftTopPoint(leftTopPoint)
{
	SetWidth(width);
	SetHeight(height);
}

CRectangle::~CRectangle()
{
}

void CRectangle::SetLeftTopPoint(sf::Vector2f leftTopPoint)
{
	m_leftTopPoint = leftTopPoint;
}

void CRectangle::SetLeftTopPoint(float x, float y)
{
	m_leftTopPoint = { x, y };
}

sf::Vector2f CRectangle::GetLeftTopPoint() const
{
	return m_leftTopPoint;
}

void CRectangle::SetWidth(float width)
{
	if (width < 0)
	{
		m_width = 0;
	}
	else
	{
		m_width = width;
	}
}

float CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetHeight(float height)
{
	if (height < 0)
	{
		m_height = 0;
	}
	else
	{
		m_height = height;
	}
}

float CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::SetLeft(float left)
{
	m_leftTopPoint.x = left;
}

float CRectangle::GetLeft() const
{
	return m_leftTopPoint.x;
}

void CRectangle::SetRight(float right)
{
	m_leftTopPoint.x = right - m_width;
}

float CRectangle::GetRight() const
{
	return m_width + GetLeft();
}

void CRectangle::SetTop(float top)
{
	m_leftTopPoint.y = top;
}

float CRectangle::GetTop() const
{
	return m_leftTopPoint.y;
}

void CRectangle::SetBottom(float bottom)
{
	m_leftTopPoint.y = bottom - m_height;
}

float CRectangle::GetBottom() const
{
	return m_leftTopPoint.y + m_height;
}

float CRectangle::GetPerimeter() const
{
	return (m_height + m_width) * 2.f;
}

float CRectangle::GetArea() const
{
	return m_height * m_width;
}

std::string CRectangle::GetStringPresentation() const
{
	std::ostringstream strm;
	strm << std::setprecision(3);

	AppendProperties(strm);

	return strm.str();
}

void CRectangle::Move(float dx, float dy)
{
	m_leftTopPoint.x += dx;
	m_leftTopPoint.y += dy;
}

void CRectangle::Scale(float sx, float sy)
{
	if ((sx > 0) && (sy > 0))
	{
		m_width *= sx;
		m_height *= sy;
	}
}

bool CRectangle::Intersect(CRectangle const & other)
{
	bool leftIsIntersect = IsBetween(GetLeft(), other.GetLeft(), other.GetRight());
	bool rightIsIntersect = IsBetween(GetRight(), other.GetLeft(), other.GetRight());
	bool topIsIntersect = IsBetween(GetTop(), other.GetTop(), other.GetBottom());
	bool bottomIsIntersect = IsBetween(GetBottom(), other.GetTop(), other.GetBottom());


	if (leftIsIntersect && topIsIntersect)
	{
		SetWidth(other.GetRight() - GetLeft());
		SetHeight(other.GetBottom() - GetTop());
		SetLeftTopPoint(sf::Vector2f(GetLeft(), GetTop()));

		return true;
	}
	else if (rightIsIntersect && topIsIntersect)
	{
		SetWidth(GetRight() - other.GetLeft());
		SetHeight(other.GetBottom() - GetTop());
		SetLeftTopPoint(sf::Vector2f(other.GetLeft(), GetTop()));

		return true;
	}
	else if (rightIsIntersect && bottomIsIntersect)
	{
		SetWidth(GetRight() - other.GetLeft());
		SetHeight(GetBottom() - other.GetTop());
		SetLeftTopPoint(sf::Vector2f(other.GetLeft(), other.GetTop()));

		return true;
	}
	else if (leftIsIntersect && bottomIsIntersect)
	{
		SetWidth(other.GetRight() - GetLeft());
		SetHeight(GetBottom() - other.GetTop());
		SetLeftTopPoint(sf::Vector2f(GetLeft(), other.GetTop()));

		return true;
	}

	m_width = 0;
	m_height = 0;
	return false;
}

void CRectangle::AppendProperties(std::ostream & strm) const
{
	CSolidShape::AppendProperties(strm);
	strm << "\tLeft top point = (" << m_leftTopPoint.x << ", "
		<< m_leftTopPoint.y << ")" << std::endl
		<< "\tWidth = " << GetWidth() << std::endl
		<< "\tHeigth = " << GetHeight() << std::endl;

}

void CRectangle::Accept(IShapeVisitor & visitor)
{
	visitor.Visit(*this);
}
