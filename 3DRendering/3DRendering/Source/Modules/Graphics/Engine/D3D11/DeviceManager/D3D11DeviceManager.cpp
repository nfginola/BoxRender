#include "D3D11DeviceManager.h"

D3D11DeviceManager::D3D11DeviceManager(const HWND& hwnd, const int& clientWidth, const int& clientHeight) :
	m_swapChain(nullptr),
	m_device(nullptr),
	m_deviceContext(nullptr),
	m_clientWidth(clientWidth),
	m_clientHeight(clientHeight),
	m_hwnd(hwnd)
{
	createDevAndSC(hwnd);
	getBackBufferRTV();
	initializeMainViewport();

	// Get Debug for printing live object details at shutdown
	HRESULT hr = m_device.Get()->QueryInterface<ID3D11Debug>(m_debug.GetAddressOf());
	assert(SUCCEEDED(hr));

}

D3D11DeviceManager::~D3D11DeviceManager()
{
	m_debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
}

void D3D11DeviceManager::clearBackBufferRTV(const FLOAT rgba[])
{
	m_deviceContext->ClearRenderTargetView(m_backBufferRTV.Get(), rgba);
}

void D3D11DeviceManager::createDevAndSC(const HWND& hwnd)
{
	DXGI_SWAP_CHAIN_DESC scDesc = { 0 };
	scDesc.BufferDesc.Width = m_clientWidth;
	scDesc.BufferDesc.Height = m_clientHeight;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;	
	scDesc.BufferDesc.RefreshRate.Denominator = 0;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// Don't forget to manually gamma correct in shader!
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	// No mutlisample settings on
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;

	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;		//  "Front buffer typically included in the BufferCount" - Double buffering
	scDesc.OutputWindow = hwnd;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;				// discard the already show buffer after present
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;			// optional flags for swap chain behaviour

	LRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,						// Default video adapter
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,						// No software
		D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG,		// Create flags
		NULL,	// Features targeted by this device, default: 11.0, 10.1, 10, 9.3, 9.2, 9.1 (6)
		0,
		D3D11_SDK_VERSION,
		&scDesc,
		m_swapChain.GetAddressOf(),
		m_device.GetAddressOf(),
		NULL,	// we dont need to keep track of which feature level is supported right now
		m_deviceContext.GetAddressOf()
	);

	assert(SUCCEEDED(hr));
}

void D3D11DeviceManager::getBackBufferRTV()
{
	// We already have the back buffer which is contained in the swap chain!
	ID3D11Texture2D* bb;
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb);
	assert(SUCCEEDED(hr));

	hr = m_device->CreateRenderTargetView(bb, NULL, m_backBufferRTV.GetAddressOf());		// NULL: create a view that accesses all of the subresources in mipmap level 0
	assert(SUCCEEDED(hr));

	bb->Release();
}

void D3D11DeviceManager::initializeMainViewport()
{
	m_mainVP.TopLeftX = 0.f;
	m_mainVP.TopLeftY = 0.f;
	m_mainVP.Width = (FLOAT)m_clientWidth;
	m_mainVP.Height = (FLOAT)m_clientHeight;
	m_mainVP.MinDepth = 0.f;
	m_mainVP.MaxDepth = 1.f;
}