#pragma once
#include <stdint.h>

namespace graphics_lib_pro
{

class ICanvas
{
public:
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

}