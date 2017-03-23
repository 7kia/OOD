#pragma once
#include <SFML/Graphics.hpp>

#include "ShapeReader.h"
#include "Painter\Painter.h"


class CApplication
{
public:
	CApplication();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void Run(const std::string & fileName);
private:
	void Render();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	sf::RenderWindow m_window;

	CShapeReader m_reader;
	std::shared_ptr<CSFMLShapeFactory> m_factory;// TODO : see need pointer
	CPainter m_painter;
};