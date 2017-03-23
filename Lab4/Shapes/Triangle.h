#pragma once


#include "IAccepter.h"
#include "LineSegment.h"
#include "CSolidShape.h"

class CTriangle final:
	public CSolidShape
{
public:
	CTriangle();
	CTriangle(
		const sf::Vector2f firstPoint
		, const sf::Vector2f secondPoint
		, const sf::Vector2f thirdPoint
		, const sf::Color fillColor
		, const sf::Color outlineColor
	);
	~CTriangle();

	float				GetPerimeter() const override;
	float				GetArea() const override;

	void				SetPositionFirstPoint(sf::Vector2f position);
	void				SetPositionFirstPoint(float x, float y);

	void				SetPositionSecondPoint(sf::Vector2f position);
	void				SetPositionSecondPoint(float x, float y);

	void				SetPositionThirdPoint(sf::Vector2f position);
	void				SetPositionThirdPoint(float x, float y);

	sf::Vector2f		GetFirstPoint() const;// for draw
	sf::Vector2f		GetSecondPoint() const;
	sf::Vector2f		GetThirdPoint() const;
private:

	void				Accept(IShapeVisitor & visitor) override;
private:
	CLineSegment		m_firstLine;
	CLineSegment		m_secondLine;
	CLineSegment		m_thirdLine;
};

