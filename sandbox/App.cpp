// boilerplate Windows init code adapted from http://www.directxtutorial.com/

#include "App.h"
#include "Log.h"

using namespace Sandbox;

#include <windows.h>
#include <windowsx.h>
#include <iostream>

using namespace std;

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_3.h>
//#include <d3dx11.h>
//#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")

void App::InitializeGraphics()
{
	Log::Info << "Initializing graphics subsystem...\n";

	//// this function initializes and prepares Direct3D for use
	//// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	//// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = m_windowHandle;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

	//// create a device, device context and swap chain using the information in the scd struct
	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_swapchain,
		&m_device,
		NULL,
		&m_deviceContext);

	if (S_OK != result)
	{
		Log::Error << "Graphics initialization failed with result " << result << endl;
	}
}

void App::ShutdownGraphics()
{
	// close and release all existing COM objects
	m_swapchain->Release();
	m_device->Release();
	m_deviceContext->Release();

}

void App::Initialize(HINSTANCE instance, LPSTR commandLine, int commandShow, int clientWidth, int clientHeight)
{
	m_clientWidth = clientWidth;
	m_clientHeight = clientHeight;

	InitializeWindows(instance, commandLine, commandShow);
	InitializeGraphics();

}


void App::InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow)
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
	wc.lpfnWndProc = &App::winProc;// WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
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

	m_windowHandle = hWnd;
}

// this is the main message handler for the program
LRESULT CALLBACK App::winProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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


void App::Shutdown()
{
	ShutdownGraphics();
}


int WINAPI App::Run()
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
	
	Shutdown();

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;

}

