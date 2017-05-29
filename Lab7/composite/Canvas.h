#pragma once
#include <ICanvas.h>
#include <memory>


class CCanvas 
	: public ICanvas
	, public sf::Drawable
{
public:
	//--------------------------------------------
	// ICanvas
	void SetLineColor(RGBAColor color) override final;
	void SetLineThickness(float thickness) override final;
	void BeginFill(RGBAColor color) override final;
	void EndFill() override;
	void MoveTo(float x, float y) override final;
	void LineTo(float x, float y) override final;
	void DrawEllipse(
		float left,
		float top,
		float width,
		float height
	) override final;
	//--------------------------------------------
	// sf::Drawable
	void draw(
		sf::RenderTarget& target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override final;
	//--------------------------------------------
private:
	std::vector<std::shared_ptr<sf::Drawable>> m_drawables;
	std::vector<sf::Vector2f> m_fillPoints;
	float m_lineThickness;
	sf::Color m_lineColor;
	sf::Color m_fillColor;
	sf::Vector2f m_lastPoint;
	bool m_isFilling = false;
};

