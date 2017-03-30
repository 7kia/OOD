#pragma once

#include "IShape.h"


static const sf::Color DEFAULT_FILL_COLOR(0, 0, 0, 0);

class CShape 
	: public IShape
{
public:
	CShape(const sf::Color & fillColor = DEFAULT_COLOR, const sf::Color & outlineColor = DEFAULT_COLOR);
public:

	void						SetFillColor(const sf::Color & color);
	sf::Color					GetFillColor() const;

	void						SetOutlineColor(const sf::Color & color) override;
	sf::Color					GetOutlineColor() const override;
protected:
	sf::Color					m_fillColor;
	sf::Color					m_outlineColor = DEFAULT_FILL_COLOR;
};