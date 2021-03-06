#pragma once
#include "ICanvas.h"

namespace graphics_lib_pro
{
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(uint32_t rgbColor) override;
		void MoveTo(int x, int y) override;
		void LineTo(int x, int y) override;

	private:
		uint32_t m_color;
	};
}