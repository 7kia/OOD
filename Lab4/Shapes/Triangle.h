#pragma once


#include "IAccepter.h"
#include "LineSegment.h"
#include "CSolidShape.h"

class CTriangle final:
	public CSolidShape
{
public:
	CTriangle();
	CTriangle(sf::Vector2f firstPoint, sf::Vector2f secondPoint, sf::Vector2f thirdPoint,
				SColor fillColor, SColor outlineColor);
	~CTriangle();

	float				GetPerimeter() const override;
	float				GetArea() const override;
	std::string			GetStringPresentation() const override;

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
	void				AppendProperties(std::ostream & strm) const;

	void				Accept(IShapeVisitor & visitor) override;
private:
	CLineSegment		m_firstLine;
	CLineSegment		m_secondLine;
	CLineSegment		m_thirdLine;
};

