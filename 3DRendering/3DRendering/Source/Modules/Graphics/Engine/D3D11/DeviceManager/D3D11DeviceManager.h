#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <assert.h>
#include <wrl/client.h>

// For easy colors
#include <DirectXColors.h>

// C++ style type definitions
using SwapChainPtr = Microsoft::WRL::ComPtr<IDXGISwapChain>;
using DevicePtr = Microsoft::WRL::ComPtr<ID3D11Device>;
using DeviceContextPtr = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
using DebugPtr = Microsoft::WRL::ComPtr<ID3D11Debug>;
using RtvPtr = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;

class D3D11DeviceManager
{
private:
	SwapChainPtr m_swapChain;
	DevicePtr m_device;
	DeviceContextPtr m_deviceContext;
	DebugPtr m_debug;

	RtvPtr m_backBufferRTV;

	D3D11_VIEWPORT m_mainVP;

	HWND m_hwnd;
	int	m_clientWidth;
	int m_clientHeight;

	void createDevAndSC(const HWND& hwnd);
	void getBackBufferRTV();
	void initializeMainViewport();


public:
	D3D11DeviceManager(const HWND& hwnd, const int& clientWidth, const int& clientHeight);
	~D3D11DeviceManager();

	// Function is const (cannot modify 'this')
	DeviceContextPtr getDeviceContext() const { return m_deviceContext; };
	DevicePtr getDevice() const { return m_device; };
	RtvPtr getRTV() const { return m_backBufferRTV; };
	SwapChainPtr getSwapChain() const { return m_swapChain; };
	DebugPtr getDebug() const { return m_debug; };
	D3D11_VIEWPORT getVP() const { return m_mainVP; };

	void clearBackBufferRTV(CONST FLOAT rgba[]);

};
