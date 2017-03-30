#include "stdafx.h"
#include "SFMLFactory.h"

namespace
{
	const float					THIKNESS_LINE = 5;
	const sf::Vector2f			ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float					RADIUS_POINT = 2.f;
}

SFMLShapePtr CSFMLShapeFactory::CreateShape(const CShapePtr & shape)
{
	shape->Accept(*this);
	return m_acceptShape;
}


void CSFMLShapeFactory::Visit(const CRectangle & data)
{
	std::shared_ptr<sf::RectangleShape> rectangle(new sf::RectangleShape);

	rectangle->setFillColor(data.GetFillColor());

	rectangle->setOutlineColor(data.GetOutlineColor());
	rectangle->setOutlineThickness(THIKNESS_LINE);

	rectangle->setSize(sf::Vector2f(data.GetSize().width, data.GetSize().height));
	rectangle->setOrigin(0.f, 0.f);// in SFML default anchor point in left top angle
	rectangle->setPosition(data.GetLeftTopPoint());

	m_acceptShape = std::move(rectangle);
}


void CSFMLShapeFactory::Visit(const CCircle & data)
{
	std::shared_ptr<sf::CircleShape> circle(new sf::CircleShape);

	circle->setFillColor(data.GetFillColor());

	circle->setOutlineColor(data.GetOutlineColor());
	circle->setOutlineThickness(THIKNESS_LINE);
	circle->setOrigin(data.GetRadius() / 2.f, data.GetRadius() / 2.f);
	circle->setPosition(data.GetPosition());

	circle->setRadius(data.GetRadius());

	m_acceptShape = std::move(circle);
}


void CSFMLShapeFactory::Visit(const CTriangle & data)
{
	std::shared_ptr<sf::ConvexShape> triangle(new sf::ConvexShape);

	triangle->setPointCount(3);

	triangle->setPoint(0, data.GetFirstPoint());
	triangle->setPoint(1, data.GetSecondPoint());
	triangle->setPoint(2, data.GetThirdPoint());

	triangle->setFillColor(data.GetFillColor());

	triangle->setOutlineColor(data.GetOutlineColor());
	triangle->setOutlineThickness(THIKNESS_LINE);

	m_acceptShape = std::move(triangle);
}
