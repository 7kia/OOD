#pragma once

#include "ISolidShape.h"

class CSolidShape :
	public ISolidShape,
	public CShape
{
public:
	CSolidShape(
		const std::string & type
		, const sf::Color fillColor
		, const sf::Color boundColor
	);
	~CSolidShape();

	void				SetOutlineColor(const sf::Color color) override;
	sf::Color			GetOutlineColor() const override;
protected:
	void				AppendProperties(std::ostream & strm) const override;
private:
	sf::Color			m_outlineColor = DEFAULT_FILL_COLOR;

};

