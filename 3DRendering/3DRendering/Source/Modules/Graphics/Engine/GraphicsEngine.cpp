#include "GraphicsEngine.h"

using namespace Graphics;

GraphicsEngine::GraphicsEngine(const HWND& hwnd, const int& clientWidth, const int& clientHeight)
{
	m_renderer = std::make_shared<D3D11Renderer>(hwnd, clientWidth, clientHeight);
}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::render(float dt)
{
	m_renderer->clearScreen(0.f, 0.f, 0.f);

	// Tech
	// batching..
	// update obj graphics

	/*
		m_renderer->GPass(...)

		m_renderer->LightPass(...)
	*/

	m_renderer->tempDraw(m_activeScene);	// e.g g-pass

	m_renderer->present();
}

void Graphics::GraphicsEngine::setScene(std::shared_ptr<Scene> scene)
{
	m_activeScene = scene;
}
