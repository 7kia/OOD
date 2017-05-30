#include "stdafx.h"
#include "Canvas.h"

using namespace std;

namespace graphics_lib_pro
{

	void CCanvas::MoveTo(int x, int y)
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}

	void CCanvas::LineTo(int x, int y)
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}

	void CCanvas::SetColor(uint32_t rgbColor)
	{
		cout << "#" << hex << setw(6) << setfill('0') << rgbColor << endl << dec;
	}

}