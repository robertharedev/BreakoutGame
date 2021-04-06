#include <Windows.h>
#include <crtdbg.h>
#include <time.h>
#include "BreakoutGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int show)
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
#endif

	srand((int)time(NULL));

	BreakoutGame window;
	window.create(hInstance, 800, 800, 100, true);

	return 0;
}