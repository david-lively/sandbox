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
		Window()
		{
			if (nullptr != m_instance)
				throw;

			m_instance = this;
		}

		~Window()
		{
			Shutdown();
		}

		int WINAPI Run();

		void Initialize(HINSTANCE instance, LPSTR commandLine, int commandShow, int clientWidth, int clientHeight);
		
		
		// get the last Windows API error.
		// Returns empty string if no error is available.
		std::string LastError();

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
			m_graphics.Clear();



			m_graphics.Present();

		}


	private:
		Window* m_instance = nullptr;
		HWND m_windowHandle = 0;
		int m_clientWidth  = -1;
		int m_clientHeight = -1;
		Graphics m_graphics;


		HWND InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow);

		void Shutdown();

		// the WindowProc function prototype
		static LRESULT CALLBACK winProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	};
}

#endif