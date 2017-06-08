#include "Editor.h"
#include <locale.h>
int main()
{
	setlocale(LC_ALL, "Russian");
	CEditor editor;
	editor.Start();
	return 0;
}
