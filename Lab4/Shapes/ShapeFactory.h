#pragma once

#include "IShapeVisitor.h"
#include "Shapes.h"

typedef typename std::vector<std::string> listArguments;

class CShapeFactory
{
public:
	CShapeFactory() = default;

	enum class IdCommand
	{
		Triangle = 0,
		Rectangle,
		Circle
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CShapePtr CreateShape(const listArguments & arguments);
private:
	std::shared_ptr<CTriangle>				CreateTriangle(const listArguments & arguments);
	std::shared_ptr<CRectangle>				CreateRectangle(const listArguments & arguments);
	std::shared_ptr<CCircle>				CreateCircle(const listArguments & arguments);

	void									CheckAmountArguments(const listArguments & arguments, IdCommand id);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};