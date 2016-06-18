#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_3.h>

#include "Log.h"

namespace Sandbox
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		bool Initialize(const HWND window, const int width = 1280, const int height = 720);

		void Clear();
		void Present();

	private:
		bool m_isInitialized = false;
		HWND m_windowHandle;
		int m_clientWidth = -1;
		int m_clientHeight = -1;

		IDXGISwapChain* m_swapchain = nullptr;             // the pointer to the swap chain interface
		ID3D11Device* m_device = nullptr;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* m_deviceContext = nullptr;
		ID3D11RenderTargetView* m_backBuffer = nullptr;
	};

}

#endif