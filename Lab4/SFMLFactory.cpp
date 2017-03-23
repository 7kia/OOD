#include "stdafx.h"
#include "SFMLFactory.h"


SFMLShapePtr CSFMLShapeFactory::CreateShape(const CShapePtr & shape)
{
	shape->Accept(*this);
	return m_acceptShape;
}

void CSFMLShapeFactory::Visit(const CLineSegment & data)
{
	std::shared_ptr<sf::RectangleShape> line(new sf::RectangleShape);

	line->setFillColor(data.GetFillColor());
	line->setSize(sf::Vector2f(THIKNESS_LINE, data.GetPerimeter()));
	line->setOrigin(ORIGIN_LINE);
	line->setPosition(data.GetFirstPoint());

	sf::Vector2f coordinateSecondPointInZeroSystemCoordinates = data.GetSecondPoint();
	coordinateSecondPointInZeroSystemCoordinates -= data.GetFirstPoint();

	float angle = (atan2(coordinateSecondPointInZeroSystemCoordinates.x,
		coordinateSecondPointInZeroSystemCoordinates.y))
		* 180.f
		/ static_cast<float>(M_PI);
	if (angle < 0)
	{
		angle += 180;
	}

	line->setRotation(angle);

	m_acceptShape = std::move(line);
}


void CSFMLShapeFactory::Visit(const CRectangle & data)
{
	std::shared_ptr<sf::RectangleShape> rectangle(new sf::RectangleShape);

	rectangle->setFillColor(data.GetFillColor());

	rectangle->setOutlineColor(data.GetOutlineColor());
	rectangle->setOutlineThickness(THIKNESS_LINE);

	rectangle->setSize(sf::Vector2f(data.GetWidth(), data.GetHeight()));
	rectangle->setOrigin(0.f, 0.f);// in SFML default anchor point in left top angle
	rectangle->setPosition(data.GetLeftTopPoint());

	m_acceptShape = std::move(rectangle);
}


void CSFMLShapeFactory::Visit(const CMyPoint & data)
{
	std::shared_ptr<sf::CircleShape> circle(new sf::CircleShape);

	circle->setFillColor(data.GetFillColor());

	circle->setOrigin(RADIUS_POINT / 2, RADIUS_POINT / 2);
	circle->setPosition(data.GetPosition());

	circle->setRadius(RADIUS_POINT);

	m_acceptShape = std::move(circle);
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
