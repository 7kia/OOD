// composite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Canvas.h"
#include <iostream>
#include <composite_lib.h>

using namespace std;


void InitSlide(CSlide & slide)
{
	// Sourse propotion
	// trianlge		50., 50., 400., 300.
	// rectangle	100., 350.0, 300., 350.
	// ellipse		200., 200., 50., 50.
	RectD triangleFrame = { 25., 25., 200., 150. };
	CTriangle triangle(
		triangleFrame,
		std::make_shared<CStyle>(true, 0xA00000FF),
		std::make_shared<CLineStyle>(true, 0x000000FF, 5.f)
	);

	RectD rectangleFrame = { 50., 175.0, 150., 175. };
	CRectangle rectangle(
		rectangleFrame,
		std::make_shared<CStyle>(false, 0xAA4400FF),
		std::make_shared<CLineStyle>(true, 0x00FF00FF, 3.f)
	);

	RectD ellipseFrame = { 100., 100., 25, 25 };	
	CEllipse ellipse(
		ellipseFrame,
		std::make_shared<CStyle>(true, 0x001DFFFF),
		std::make_shared<CLineStyle>(false, 0x000000FF, 3.f)
	);

	auto group = std::make_shared<CGroup>();
	group->InsertShape(make_shared<CRectangle>(rectangle), 0);
	group->InsertShape(make_shared<CTriangle>(triangle), 1);
	group->InsertShape(make_shared<CEllipse>(ellipse), 2);

	RectD groupFrame = { 300., 150., 500., 300. };
	group->SetFrame(groupFrame);
	slide.AddShape(make_shared<CRectangle>(rectangle));
	slide.AddShape(make_shared<CTriangle>(triangle));
	slide.AddShape(make_shared<CEllipse>(ellipse));
	slide.AddShape(group);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Lab 7 \"Composite\"");
	CCanvas canvas(window);
	CSlide slide;
	InitSlide(slide);
	slide.Draw(canvas);
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		canvas.draw(window, sf::RenderStates::Default);
		window.display();
	}

	return 0;
}

