#pragma once

#include <boost/math/constants/constants.hpp>

#include "IShape.h"

class CShape :
	public IShape
{
public:
	CShape(const std::string & type, SColor color);
	~CShape();

	void						SetFillColor(SColor color);
	void						SetFillColor(uint8_t r, uint8_t g, uint8_t b);
	SColor						GetFillColor() const;

	std::string					GetType() const;// for render

	void						AppendProperties(std::ostream & strm) const override;

protected:
	SColor						m_fillColor;
	std::string					m_type;
};