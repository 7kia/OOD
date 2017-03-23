#pragma once

#include "IAccepter.h"
#include "MyCPoint.h"

class CLineSegment final :
	public CShape
{
public:
	CLineSegment();
	CLineSegment(
		const sf::Vector2f firstPoint
		, const sf::Vector2f secondPoint
		, const sf::Color color
	);
	~CLineSegment();

	float				GetPerimeter() const override;
	float				GetArea() const override;
	std::string			GetStringPresentation() const override;

	void				SetPositionFirstPoint(sf::Vector2f position);
	void				SetPositionFirstPoint(float x, float y);
	sf::Vector2f		GetFirstPoint() const;

	void				SetPositionSecondPoint(sf::Vector2f position);
	void				SetPositionSecondPoint(float x, float y);
	sf::Vector2f		GetSecondPoint() const;
private:
	void				AppendProperties(std::ostream & strm) const;

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_firstPoint;
	sf::Vector2f		m_secondPoint;
};
