#pragma once

#include "IAccepter.h"
#include "CSolidShape.h"

class CCircle final :
	public CSolidShape
{
public:
	CCircle();
	CCircle(
		const sf::Vector2f center
		, float radius
		, const sf::Color fillColor
		, const sf::Color outlineColor
	);
	~CCircle();

	float				GetPerimeter() const override;
	float				GetArea() const override;
	std::string			GetStringPresentation() const override;

	void				SetRadius(float radius);
	float				GetRadius() const;

	void				SetPositionCenter(float x, float y);
	void				SetPositionCenter(sf::Vector2f position);
	sf::Vector2f		GetPosition() const;
private:
	void				AppendProperties(std::ostream & strm) const;

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_positionCenter;
	float				m_radius = 0.f;
};

