// include the basic windows header file
#include <windows.h>

#include "App.h"

using namespace Sandbox;

#include "guicon.h"


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

#ifdef _DEBUG
	RedirectIOToConsole();
#endif

	App app;

	app.Initialize(hInstance, lpCmdLine, nCmdShow, 1280, 720);

	return app.Run();
}
