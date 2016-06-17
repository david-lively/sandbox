#ifndef	APP_H
#define APP_H

#include <windows.h>

#include "Log.h"

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
			Log::Info << "Update\n";

		}

		virtual void Render()
		{
			Log::Info << "Render\n";

		}


	private:
		App* m_instance = nullptr;
		HWND m_windowHandle;
		int m_clientWidth = -1;
		int m_clientHeight = -1;

		void InitializeGraphicsSystem();
		void InitializeWindows(HINSTANCE instance, LPSTR commandLine, int commandShow);

		// the WindowProc function prototype
		static LRESULT CALLBACK winProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);


	};
}

#endif