#pragma once
#include "IVisitor.h"

class IAccepter {
public:
	virtual void Accept(IShapeVisitor & visitor) = 0;
	virtual ~IAccepter() = default;
};