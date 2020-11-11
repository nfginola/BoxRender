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

void D3D11Renderer::clearScreen(float r, float g, float b)
{
	if (r > 255.f) r = 255.f;
	if (g > 255.f) g = 255.f;
	if (b > 255.f) b = 255.f;
	const FLOAT color[4] = {r / 255.f, g / 255.f, b / 255.f, 1.f};

	m_devMan->clearBackBufferRTV(color);
}

void D3D11Renderer::present()
{
	m_devMan->getSwapChain()->Present(0, 0);
}

void Graphics::D3D11Renderer::bindShader(std::shared_ptr<IShader> shader)
{
	shader->bind(m_devMan->getDeviceContext());
}

void Graphics::D3D11Renderer::unbindShader(std::shared_ptr<IShader> shader)
{
	shader->unbind(m_devMan->getDeviceContext());
}


