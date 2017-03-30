#pragma once


#include "CShape.h"

class CTriangle final:
	public CShape
{
public:
	CTriangle() = default;
	CTriangle(
		const sf::Vector2f & firstPoint
		, const sf::Vector2f & secondPoint
		, const sf::Vector2f  & thirdPoint
		, const sf::Color & fillColor
		, const sf::Color & outlineColor
	);

public:
	void				SetFirstPoint(const sf::Vector2f & position);
	void				SetSecondPoint(const sf::Vector2f & position);
	void				SetThirdPoint(const sf::Vector2f & position);

	sf::Vector2f		GetFirstPoint() const;
	sf::Vector2f		GetSecondPoint() const;
	sf::Vector2f		GetThirdPoint() const;
private:

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_firstPoint;
	sf::Vector2f		m_secondPoint;
	sf::Vector2f		m_thirdPoint;
};

