#include "stdafx.h"
#include "ShapeVisitor.h"

void CShapeVisitor::Visit(const CLineSegment & data)
{
	std::shared_ptr<sf::RectangleShape> line(new sf::RectangleShape);

	SColor color = data.GetFillColor();
	line->setFillColor(sf::Color(color.red, color.green, color.blue));
	line->setSize(sf::Vector2f(THIKNESS_LINE, data.GetPerimeter()));
	line->setOrigin(ORIGIN_LINE);
	line->setPosition(data.GetPositiionFirstPoint());

	sf::Vector2f coordinateSecondPointInZeroSystemCoordinates = data.GetPositiionSecondPoint();
	coordinateSecondPointInZeroSystemCoordinates -= data.GetPositiionFirstPoint();

	float angle = (atan2(coordinateSecondPointInZeroSystemCoordinates.x,
						coordinateSecondPointInZeroSystemCoordinates.y)) 
					* 180.f 
					/ static_cast<float>(M_PI);
	if (angle < 0) {
		angle += 180;
	}

	line->setRotation(angle);

	m_acceptShape = std::move(line);
}


void CShapeVisitor::Visit(const CRectangle & data)
{
	std::shared_ptr<sf::RectangleShape> rectangle(new sf::RectangleShape);

	SColor fillColor = data.GetFillColor();
	rectangle->setFillColor(sf::Color(fillColor.red, fillColor.green, fillColor.blue));
	
	SColor outlineColor = data.GetOutlineColor();
	rectangle->setOutlineColor(sf::Color(outlineColor.red, outlineColor.green, outlineColor.blue));
	rectangle->setOutlineThickness(THIKNESS_LINE);

	rectangle->setSize(sf::Vector2f(data.GetWidth(), data.GetHeight()));
	rectangle->setOrigin(0.f, 0.f);// in SFML default anchor point in left top angle
	rectangle->setPosition(data.GetLeftTopPoint());

	m_acceptShape = std::move(rectangle);
}


void CShapeVisitor::Visit(const MyCPoint & data)
{
	std::shared_ptr<sf::CircleShape> circle(new sf::CircleShape);

	SColor fillColor = data.GetFillColor();
	circle->setFillColor(sf::Color(fillColor.red, fillColor.green, fillColor.blue));

	circle->setOrigin(RADIUS_POINT / 2, RADIUS_POINT / 2);
	circle->setPosition(data.GetPosition());

	circle->setRadius(RADIUS_POINT);

	m_acceptShape = std::move(circle);
}


void CShapeVisitor::Visit(const CCircle & data)
{
	std::shared_ptr<sf::CircleShape> circle(new sf::CircleShape);

	SColor fillColor = data.GetFillColor();
	circle->setFillColor(sf::Color(fillColor.red, fillColor.green, fillColor.blue));

	SColor outlineColor = data.GetOutlineColor();
	circle->setOutlineColor(sf::Color(outlineColor.red, outlineColor.green, outlineColor.blue));
	circle->setOutlineThickness(THIKNESS_LINE);
	circle->setOrigin(data.GetRadius() / 2.f, data.GetRadius() / 2.f);
	circle->setPosition(data.GetPosition());

	circle->setRadius(data.GetRadius());

	m_acceptShape = std::move(circle);
}


void CShapeVisitor::Visit(const CTriangle & data)
{
	std::shared_ptr<sf::ConvexShape> triangle(new sf::ConvexShape);

	triangle->setPointCount(3);

	triangle->setPoint(0, data.GetFirstPoint());
	triangle->setPoint(1, data.GetSecondPoint());
	triangle->setPoint(2, data.GetThirdPoint());

	SColor fillColor = data.GetFillColor();
	triangle->setFillColor(sf::Color(fillColor.red, fillColor.green, fillColor.blue));

	SColor outlineColor = data.GetOutlineColor();
	triangle->setOutlineColor(sf::Color(outlineColor.red, outlineColor.green, outlineColor.blue));
	triangle->setOutlineThickness(THIKNESS_LINE);

	m_acceptShape = std::move(triangle);
}

std::shared_ptr<sf::Shape> CShapeVisitor::GetAcceptShape()
{
	return m_acceptShape;
}
