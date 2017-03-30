#pragma once

#include <SFML/Graphics.hpp>
#include "..\PictureDraft.h"
#include "..\SFMLFactory.h"

class CPainter
{
public:
	CPainter() = default;
	CPainter(const std::shared_ptr<ISFMLShapeFactory> & pFactory);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void			SetShapeFactory(const std::shared_ptr<ISFMLShapeFactory> & pFactory);
	void			SetPictureDraft(const CPictureDraft & draft);
	void			DrawPicture(sf::RenderWindow & window);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::shared_ptr<ISFMLShapeFactory> m_pFactory;
	std::vector<SFMLShapePtr> m_shapes;
};