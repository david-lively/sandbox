// include the basic windows header file
#include <windows.h>
#include <iostream>

using namespace std;

#include "Window.h"
#include "Log.h"

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

	Window app;

	app.Initialize(hInstance, lpCmdLine, nCmdShow, 1280, 720);

	auto result = app.Run();

	Log::Info << "Press enter to continue." << endl;
	getchar();

	return result;
}
