#pragma once

#include "CShape.h"

class CCircle final :
	public CShape
{
public:
	CCircle() = default;
	CCircle(
		const sf::Vector2f center
		, float radius
		, const sf::Color fillColor
		, const sf::Color outlineColor
	);
public:
	void				SetRadius(float radius);
	float				GetRadius() const;

	void				SetPosition(sf::Vector2f position);
	sf::Vector2f		GetPosition() const;
private:
	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_positionCenter;
	float				m_radius = 0.f;
};

