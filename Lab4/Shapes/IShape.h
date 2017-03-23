#pragma once

#include "SFML\Graphics.hpp"
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "IAccepter.h"


static const float pi = boost::math::constants::pi<float>();
static const std::string MESSAGE_INCORRECT_VALUE = "Incorrect value!!!";


static const sf::Color DEFAULT_COLOR(0, 0, 0, 0);
static const int AMOUNT_NUMBERS_FOR_OUTPUT = 3;

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f & vector);


// TODO : rewrite
std::ostream& operator<<(std::ostream& stream, const sf::Color color);
sf::Color ToColor(const std::string &value);

class IShape
	: public IAccepter
{
public:
	virtual ~IShape();

	virtual float				GetPerimeter() const = 0;
	virtual float				GetArea() const = 0;
};

