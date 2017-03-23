#include "Painter.h"

CPainter::CPainter(const std::shared_ptr<ISFMLShapeFactory> pFactory)
	: m_pFactory(pFactory)
{
}

void CPainter::SetShapeFactory(const std::shared_ptr<ISFMLShapeFactory> pFactory)
{
	m_pFactory = pFactory;
}

void CPainter::SetPictureDraft(const CPictureDraft & draft)
{
	for (const auto & shape : draft)
	{
		m_shapes.push_back(m_pFactory->CreateShape(shape));
	}
}

void CPainter::DrawPicture(sf::RenderWindow & window)
{
	window.clear();

	for (auto& shape : m_shapes)
	{
		window.draw(*shape);
	}

	window.display();
}
