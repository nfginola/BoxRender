#include "GraphicsEngine.h"

using namespace Graphics;

GraphicsEngine::GraphicsEngine(const HWND& hwnd, const int& clientWidth, const int& clientHeight)
{
	m_renderer = std::make_shared<D3D11Renderer>(hwnd, clientWidth, clientHeight);

	ShaderService& shdService = ShaderService::getInstance();

	shdService.addShader(ShaderType::VERTEX_SHADER, "VertexShader.cso", "vs");
	shdService.addShader(ShaderType::PIXEL_SHADER, "PixelShader.cso", "ps");
	shdService.addShader(ShaderType::GEOMETRY_SHADER, "GeometryShader.cso", "gs");
	shdService.addShader(ShaderType::DOMAIN_SHADER, "DomainShader.cso", "ds");
	shdService.addShader(ShaderType::HULL_SHADER, "HullShader.cso", "hs");
	shdService.addShader(ShaderType::COMPUTE_SHADER, "ComputeShader.cso", "cs");

	ShaderService& hehe = ShaderService::getInstance();

}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::render(float dt)
{

	// Tech
	// batching..
	// update objs

	m_renderer->clearScreen(0.f, 0.f, 0.f);
	m_renderer->present();
}