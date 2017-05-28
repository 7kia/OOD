#include "stdafx.h"
#include "Canvas.h"



CCanvas::CCanvas(sf::RenderTarget & renderTarget)
	: m_renderTarget(renderTarget)
{

}


void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = sf::Color(color);
}

void CCanvas::SetLineThickness(float thickness)
{
	m_lineThickness = thickness;
}

void CCanvas::BeginFill(RGBAColor color)
{
	if (m_isFilling)
	{
		throw std::logic_error("canvas already filling");
	}

	m_fillPoints.clear();
	m_isFilling = true;
	m_fillColor = sf::Color(color);
}

void CCanvas::EndFill()
{
	if (!m_isFilling)
	{
		throw std::logic_error("canvas doesnt filling");
	}

	m_isFilling = false;

	auto shape = std::make_shared<sf::ConvexShape>();
	shape->setPointCount(m_fillPoints.size());
	for (size_t i = 0 ; i < m_fillPoints.size(); ++i)
	{
		shape->setPoint(i, m_fillPoints[i]);
	}
	shape->setFillColor(m_fillColor);

	m_drawables.push_back(shape);
}

void CCanvas::MoveTo(double x, double y)
{
	m_lastPoint = sf::Vector2f((float)x, (float)y);
	if (m_isFilling)
	{
		m_fillPoints.push_back(m_lastPoint);
	}
}

void CCanvas::LineTo(double x, double y)
{
	float dx = (float)x - m_lastPoint.x;
	float dy = (float)y - m_lastPoint.y;
	float rotation = atan2f((float)dy, (float)dx) * 180.f / (float)M_PI;

	auto rect = std::make_shared<sf::RectangleShape>();
	rect->setSize(sf::Vector2f(sqrtf((dx * dx) + (dy * dy)) + m_lineThickness * 2.f, m_lineThickness));
	rect->setOrigin(m_lineThickness, m_lineThickness);
	rect->setPosition(m_lastPoint.x, m_lastPoint.y);
	rect->setRotation(rotation);
	rect->setFillColor(m_lineColor);

	m_renderTarget.draw(*rect);
	m_drawables.push_back(rect);
	MoveTo(x, y);

}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto ellipse = std::make_shared<sf::CircleShape>((float) height);
	ellipse->scale((float)(width / height), 1);
	ellipse->setPosition((float)left, (float)top);
	ellipse->setOutlineColor(m_lineColor);
	ellipse->setOutlineThickness(m_lineThickness);

	if (m_isFilling)
	{
		ellipse->setFillColor(m_fillColor);
	}
	else
	{
		ellipse->setFillColor(sf::Color::Transparent);
	}
	m_renderTarget.draw(*ellipse);
	m_drawables.push_back(ellipse);
}

void CCanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto & shape : m_drawables)
	{
		target.draw(*shape, states);
	}
}

