#include "Graphics.h"
#include "Log.h"
#include "Common.h"

using namespace Sandbox;

#include <d3d11.h>
#include <dxgi.h>
//#include <dxgi1_3.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

using namespace std;

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	if (m_isInitialized)
	{
		// close and release all existing COM objects
		m_swapchain->Release();
		m_backBuffer->Release();
		m_device->Release();
		m_deviceContext->Release();
	}

}

bool Graphics::Initialize(const HWND window, const int width, const int height)
{
	/// see also http://www.directxtutorial.com/Lesson.aspx?lessonid=11-4-3
	Log::Info << "Initializing graphics subsystem" << endl;

	//// this function initializes and prepares Direct3D for use
	//// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	//// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = window;                                // the window to be used
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
		Log::Error << Log::LastWinError() << endl;
		return false;
	}

	m_windowHandle = window;

	// set up the render target

	ID3D11Texture2D* backBufferPtr;
	m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);

	m_device->CreateRenderTargetView(backBufferPtr, nullptr, &m_backBuffer);
	backBufferPtr->Release();

	m_deviceContext->OMSetRenderTargets(1, &m_backBuffer, nullptr);


	Log::Info << "Configuring viewport" << endl;

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;

	m_deviceContext->RSSetViewports(1, &viewport);

	m_isInitialized = true;

	Log::Info << "Graphics initialized." << endl;

	return m_isInitialized;

}

void Graphics::Clear()
{
	Color clearColor;
	// clear the back buffer to a deep blue
	m_deviceContext->ClearRenderTargetView(m_backBuffer, (const float*)&clearColor);

}

void Graphics::Present()
{
	// do 3D rendering on the back buffer here

	// switch the back buffer and the front buffer
	m_swapchain->Present(0, 0);
}

