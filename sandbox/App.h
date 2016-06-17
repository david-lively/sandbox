#ifndef	APP_H
#define APP_H

#include <windows.h>

namespace Sandbox
{
	class App
	{
	public:
		int WINAPI winMain(
			HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR lpCmdLine,
			int nCmdShow
			);

		// the WindowProc function prototype
		static LRESULT CALLBACK winProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	private:
	};
}

#endif