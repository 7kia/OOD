#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Shapes\Shapes.h"

typedef std::shared_ptr<sf::Shape> SFMLShapePtr;

class ISFMLShapeFactory
{
public:
	virtual ~ISFMLShapeFactory() = default;

	virtual SFMLShapePtr CreateShape(const CShapePtr & shape) = 0;
};

class CSFMLShapeFactory 
	: private IShapeVisitor
	, public ISFMLShapeFactory
{
public:
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// ISFMLShapeFactory
	SFMLShapePtr				CreateShape(const CShapePtr & shape) override;
	//--------------------------------------------

private:
	//--------------------------------------------
	// IShapeVisitor
	void						Visit(const CTriangle & triangle) override;
	void						Visit(const CRectangle & rectangle) override;
	void						Visit(const CCircle & circle) override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::shared_ptr<sf::Shape>	m_acceptShape;
};