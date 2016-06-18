#ifndef	APP_H
#define APP_H

#include "Log.h"
#include "Graphics.h"

#include <windows.h>
#include <string>

namespace Sandbox
{
	class Window
	{
	public:
		Window();

		~Window();

		int WINAPI Run();

		void Initialize(HINSTANCE instance, LPSTR commandLine, int commandShow, bool fullscreen, int clientWidth = 1280, int clientHeight = 720);

		Graphics& GetGraphics() const
		{
			return *m_graphics;
		}
		
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
			m_graphics->Clear();
			m_graphics->Present();
		}


	private:
		Window* m_instance = nullptr;
		HWND m_windowHandle = 0;
		int m_clientWidth  = -1;
		int m_clientHeight = -1;
		Graphics* m_graphics = nullptr;


		HWND InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow, bool fullscreen);

		// the WindowProc function prototype
		static LRESULT CALLBACK winProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	};
}

#endif