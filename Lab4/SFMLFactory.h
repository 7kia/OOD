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
	: public IShapeVisitor
	, public ISFMLShapeFactory
{
public:
	const float					THIKNESS_LINE = 5;
	const sf::Vector2f			ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float					RADIUS_POINT = 2.f;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShapeVisitor
	void						Visit(const CLineSegment & line) override;
	void						Visit(const CTriangle & triangle) override;
	void						Visit(const CRectangle & rectangle) override;
	void						Visit(const CCircle & circle) override;
	void						Visit(const MyCPoint & point) override;
	//--------------------------------------------
	// ISFMLShapeFactory
	SFMLShapePtr				CreateShape(const CShapePtr & shape) override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::shared_ptr<sf::Shape>	m_acceptShape;
};