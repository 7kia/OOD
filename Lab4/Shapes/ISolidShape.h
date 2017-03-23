#pragma once

#include "CShape.h"

static const SColor DEFAULT_FILL_COLOR(0, 0, 0);

class ISolidShape
	: public IShape
{
public:
	virtual void				SetOutlineColor(uint8_t r, uint8_t g, uint8_t b) = 0;
	virtual void				SetOutlineColor(SColor color) = 0;
	virtual SColor				GetOutlineColor() const = 0;
};

