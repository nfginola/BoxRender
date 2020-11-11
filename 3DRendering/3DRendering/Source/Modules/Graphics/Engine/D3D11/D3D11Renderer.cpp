#include "D3D11Renderer.h"

using namespace Graphics;

D3D11Renderer::D3D11Renderer(const HWND& hwnd, const int& clientWidth, const int& clientHeight)
{
	m_devMan = std::make_unique<D3D11DeviceManager>(hwnd, clientWidth, clientHeight);

	// Initialize shader service
	ShaderService& shdServ = ShaderService::getInstance();
	shdServ.addDev(m_devMan->getDevice());
}

D3D11Renderer::~D3D11Renderer()
{
}

// [0, 1]
void D3D11Renderer::clearScreen(float r, float g, float b)
{
	const FLOAT color[4] = {r, g, b, 1.f};
	m_devMan->clearBackBufferRTV(color);
}

void D3D11Renderer::present()
{
	m_devMan->getSwapChain()->Present(0, 0);
}

void Graphics::D3D11Renderer::bindShader(IShader* shader)
{
	shader->bind(m_devMan->getDeviceContext());
}

void Graphics::D3D11Renderer::unbindShader(IShader* shader)
{
	shader->unbind(m_devMan->getDeviceContext());
}

