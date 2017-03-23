#pragma once

#include "ISolidShape.h"

class CSolidShape :
	public ISolidShape,
	public CShape
{
public:
	CSolidShape(const std::string & type, SColor boundColor, SColor fillColor);
	~CSolidShape();

	void				SetOutlineColor(uint8_t r, uint8_t g, uint8_t b) override;
	void				SetOutlineColor(SColor color) override;
	SColor				GetOutlineColor() const override;
protected:
	void				AppendProperties(std::ostream & strm) const override;
private:
	SColor				m_outlineColor = DEFAULT_FILL_COLOR;

};

