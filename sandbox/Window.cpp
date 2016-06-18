// boilerplate Windows init code adapted from http://www.directxtutorial.com/

#include "Window.h"
#include "Log.h"

using namespace Sandbox;

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <string>

using namespace std;

Window::Window()
{
	if (nullptr != m_instance)
		throw;

	m_instance = this;
}

Window::~Window()
{
	if (nullptr != m_graphics)
		delete m_graphics;
}


void Window::Initialize(HINSTANCE instance, LPSTR commandLine, int commandShow, bool fullscreen, int clientWidth, int clientHeight)
{
	m_clientWidth = clientWidth;
	m_clientHeight = clientHeight;

	m_windowHandle = InitializeWindows(instance, commandLine, commandShow, fullscreen);

	m_graphics = new Graphics();
	m_graphics->Initialize(m_windowHandle, fullscreen, clientWidth, clientHeight);
}


HWND Window::InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow, bool fullscreen)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &Window::winProc;// WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!fullscreen)
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.lpszClassName = "SandboxClass";

	// register the window class
	RegisterClassEx(&wc);

	RECT wr = { 0, 0, m_clientWidth, m_clientHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		"SandboxClass",    // name of the window class
		"DX11 Sandbox",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		wr.right - wr.left,
		wr.bottom - wr.top,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		instance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, commandShow);

	return hWnd;
}

// this is the main message handler for the program
LRESULT CALLBACK Window::winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
		// close the application entirely
		PostQuitMessage(0);
		return 0;
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}



int WINAPI Window::Run()
{
	// this struct holds Windows event messages
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			if (WM_QUIT == msg.message)
				break;
		}
		else
		{
			DoFrame();
		}
	}
	
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;

}
