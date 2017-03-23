#pragma once

#include <boost/math/constants/constants.hpp>

#include "IShape.h"

class CShape :
	public IShape
{
public:
	CShape(const std::string & type, const sf::Color color);
	~CShape();

	void						SetFillColor(const sf::Color color);
	void						SetFillColor(uint8_t r, uint8_t g, uint8_t b);
	sf::Color					GetFillColor() const;

	std::string					GetType() const;// for render


protected:
	sf::Color					m_fillColor;
	std::string					m_type;
};