#include "stdafx.h"
#include "ModernGraphicsRenderer.h"
#include <ostream>
#include <boost\format.hpp>

using namespace std;

namespace modern_graphics_lib_pro
{

	CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream & strm)
		: m_out(strm)
	{

	}

	CModernGraphicsRenderer::~CModernGraphicsRenderer()
	{
		if (m_drawing) 
		{
			EndDraw();
		}
	}

	void CModernGraphicsRenderer::BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	void CModernGraphicsRenderer::DrawLine(
		const CPoint & start,
		const CPoint & end,
		const CRGBAColor& color
	)
	{
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		auto lineFormat = boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)");
		auto colorFormat = boost::format(R"(    <color r="%1$.2f" g="%2$.2f" b="%3$.2f" a="%4$.2f" />)");
		m_out << lineFormat % start.x % start.y % end.x % end.y << endl
			<< colorFormat % color.r % color.g % color.b % color.a << endl
			<< R"(  </line>)" << endl;
	}

	void CModernGraphicsRenderer::EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}

}