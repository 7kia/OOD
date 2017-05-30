#pragma once
#include "..\graphics_lib_pro\ICanvas.h"

namespace shape_drawing_lib_pro
{

class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib_pro::ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};

}