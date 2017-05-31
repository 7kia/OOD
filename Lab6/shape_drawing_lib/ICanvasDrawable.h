#pragma once
#include "..\graphics_lib\ICanvas.h"

namespace shape_drawing_lib
{
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};
}