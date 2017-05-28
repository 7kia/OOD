#pragma once
#include "..\composite_lib\ICanvas.h"
#include <memory>


class CCanvas : public ICanvas, public sf::Drawable
{
public: 
	CCanvas(sf::RenderTarget & renderTarget);

	void SetLineColor(RGBAColor color) override;
	void SetLineThickness(float thickness) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RenderTarget & m_renderTarget;
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<sf::Vector2f> m_fillPoints;
	float m_lineThickness;
	sf::Color m_lineColor;
	sf::Color m_fillColor;
	sf::Vector2f m_lastPoint;
	bool m_isFilling = false;
};

