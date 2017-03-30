#include "stdafx.h"
#include "Application.h"

using namespace sf;

CApplication::CApplication()
	:  m_window(sf::VideoMode(960, 600), "4 laboratory work with SFML!", sf::Style::Close)
	, m_factory(std::make_shared<CSFMLShapeFactory>())
	, m_painter(m_factory)
{
}

void CApplication::Run(const std::string & fileName)
{
	m_reader.ReadShapes(fileName);
	m_painter.SetPictureDraft(m_reader.GetDraft());

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		Render();
	}
}

void CApplication::Render()
{
	m_painter.DrawPicture(m_window);
}