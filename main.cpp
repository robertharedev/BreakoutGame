#include <Windows.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int show)
{
#ifdef _DEBUG
	_onexit(_CrtDumpMemoryLeaks);
#endif

	 window;
	window.create(hInstance, 800, 600, 100, true);

	return 0;
}