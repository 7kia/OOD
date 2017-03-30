#pragma once

#include "SFML\Graphics.hpp"
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "IVisitor.h"

static const sf::Color DEFAULT_COLOR(0, 0, 0, 0);

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f & vector);
std::ostream& operator<<(std::ostream& stream, const sf::Color color);
sf::Color ToColor(const std::string &value);

struct SSize
{
	SSize() = default;
	SSize(float width, float height);

	bool operator==(SSize const& size) const;
	SSize& operator=(const SSize& right);

	float width = 0.f;
	float height = 0.f;
};

class IShape
{
public:
	virtual ~IShape() = default;;

	virtual void				SetFillColor(const sf::Color color) = 0;
	virtual sf::Color			GetFillColor() const = 0;

	virtual void				SetOutlineColor(const sf::Color color) = 0;
	virtual sf::Color			GetOutlineColor() const = 0;

	virtual void				Accept(IShapeVisitor & visitor) = 0;
};

