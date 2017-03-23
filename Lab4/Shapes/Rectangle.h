#pragma once


#include "IAccepter.h"
#include "LineSegment.h"
#include "CSolidShape.h"

class CRectangle final :// was exported from lab 3 Rectangle
	public CSolidShape
{
public:
	CRectangle();
	CRectangle(
		const sf::Vector2f leftTopPoint
		, float width
		, float height
		, const sf::Color fillColor
		, const sf::Color outlineColor
	);
	~CRectangle();

	void				SetLeftTopPoint(sf::Vector2f leftTopPoint);
	void				SetLeftTopPoint(float x, float y);
	sf::Vector2f		GetLeftTopPoint() const;

	void				SetWidth(float width);
	float				GetWidth() const;

	void				SetHeight(float height);
	float				GetHeight() const;

	void				SetLeft(float left);
	float				GetLeft() const;

	void				SetRight(float right);
	float				GetRight() const;

	void				SetTop(float top);
	float				GetTop() const;

	void				SetBottom(float bottom);
	float				GetBottom() const;

	float				GetPerimeter() const override;
	float				GetArea() const override;
	std::string			GetStringPresentation() const override;

	void				Move(float dx, float dy);
	void				Scale(float sx, float sy);
	bool				Intersect(CRectangle const& other);
private:
	void				AppendProperties(std::ostream & strm) const;

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_leftTopPoint;
	float				m_width;
	float				m_height;
};