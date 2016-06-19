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

	app.Initialize(hInstance, lpCmdLine, nCmdShow, false, 1920, 1200); // 1280, 720);
	app.GetGraphics().ClearColor.Set(0.f, 0.2f, 0.4f, 1.f);

	auto result = app.Run();

#if 0

	Log::Info << "Press enter to continue." << endl;
	getchar();

#endif

	return result;
}
