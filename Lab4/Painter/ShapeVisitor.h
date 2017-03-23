#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Shapes\CShape.h"
#include "ShapeReader.h"

typedef std::vector<std::shared_ptr<sf::Shape>> ListRenderShapes;

class CShapeVisitor : public IShapeVisitor
{
public:
	const float					THIKNESS_LINE = 5;
	const sf::Vector2f			ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float					RADIUS_POINT = 2.f;
public:
	void						Visit(const CLineSegment & line) override;
	void						Visit(const CTriangle & triangle) override;
	void						Visit(const CRectangle & rectangle) override;
	void						Visit(const CCircle & circle) override;
	void						Visit(const MyCPoint & point) override;

	std::shared_ptr<sf::Shape>	GetAcceptShape();
private:
	std::shared_ptr<sf::Shape>	m_acceptShape;
};