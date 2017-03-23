#pragma once

#include "CShape.h"

static const sf::Color DEFAULT_FILL_COLOR(0, 0, 0, 0);

class ISolidShape
	: public IShape
{
public:
	virtual void				SetOutlineColor(const sf::Color color) = 0;
	virtual sf::Color			GetOutlineColor() const = 0;
};

