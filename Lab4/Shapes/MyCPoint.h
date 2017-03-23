#pragma once

#include "CShape.h"

class MyCPoint final:
	public CShape
{
public:
	MyCPoint();
	MyCPoint(sf::Vector2f position, SColor color);
	~MyCPoint();

	float				GetPerimeter() const override;
	float				GetArea() const override;
	std::string			GetStringPresentation() const override;

	void				SetPosition(sf::Vector2f position);
	void				SetPosition(float x, float y);
	sf::Vector2f		GetPosition() const;
private:
	void				AppendProperties(std::ostream & strm) const;

	void				Accept(IShapeVisitor & visitor) override;
private:
	sf::Vector2f		m_position;
};

