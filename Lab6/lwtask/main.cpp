#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <cstdint>

#include "../modern_graphics_lib/ModernGraphicsRenderer.h"

#include "../graphics_lib/Canvas.h"
#include "../graphics_lib_pro/Canvas.h"

#include "../shape_drawing_lib/Rectangle.h"
#include "../shape_drawing_lib/CanvasPainter.h"
#include "../shape_drawing_lib/Triangle.h"

#include "../shape_drawing_lib_pro/Rectangle.h"
#include "../shape_drawing_lib_pro/CanvasPainter.h"
#include "../shape_drawing_lib_pro/Triangle.h"

#include "../GraphicLibraryAdapters/CanvasClassAdapter.h"
#include "../GraphicLibraryAdapters/CanvasColoredAdapter.h"
#include "../GraphicLibraryAdapters/CanvasObjectAdapter.h"

using namespace std;
using namespace shape_drawing_lib;

namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
	{

		CTriangle triangle({ 0, 0 }, { 100, 100 }, { 75, 100 });
		CRectangle rectangle({ 0, 1 }, 100, 75);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		CCanvasObjectAdapter adapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(adapter);
		PaintPicture(painter);
	}
}

int main()
{
	try
	{
		cout << "Should we use new API (y)?";
		string userInput;
		if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
		{
			app::PaintPictureOnModernGraphicsRenderer();
		}
		else
		{
			app::PaintPictureOnCanvas();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


	return 0;
}

