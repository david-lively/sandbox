// include the basic windows header file
#include <windows.h>

#include "App.h"

using namespace Sandbox;

App app;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	return app.winMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
