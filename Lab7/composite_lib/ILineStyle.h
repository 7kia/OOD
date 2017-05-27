#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual float GetLineThikness() const = 0;
	virtual void SetLineThikness(float thikness) = 0;
};

using ILineStylePtr = std::shared_ptr<ILineStyle>;

bool operator==(ILineStylePtr const& first, ILineStylePtr const& second);