#ifndef	APP_H
#define APP_H

#include "Log.h"

#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_3.h>

namespace Sandbox
{
	class App
	{
	public:
		App()
		{
			if (nullptr != m_instance)
				throw;

			m_instance = this;
		}

		int WINAPI Run();

		void Initialize(HINSTANCE instance, LPSTR commandLine, int commandShow, int clientWidth, int clientHeight);


		void DoFrame()
		{
			Update();
			Render();
		}

		virtual void Update()
		{
		}

		virtual void Render()
		{
		}


	private:
		App* m_instance = nullptr;
		HWND m_windowHandle;
		int m_clientWidth = -1;
		int m_clientHeight = -1;

		IDXGISwapChain* m_swapchain = nullptr;             // the pointer to the swap chain interface
		ID3D11Device* m_device = nullptr;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* m_deviceContext = nullptr;

		void InitializeGraphics();
		void InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow);

		void Shutdown();
		void ShutdownGraphics();

		// the WindowProc function prototype
		static LRESULT CALLBACK winProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	};
}

#endif