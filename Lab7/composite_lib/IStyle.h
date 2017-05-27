#pragma once
#include "CommonTypes.h"

class IStyle
{
public:
	virtual ~IStyle() = default;

	virtual bool IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual RGBAColor GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;
};

using IStylePtr = std::shared_ptr<IStyle>;


bool operator==(IStylePtr const& first, IStylePtr const& second);