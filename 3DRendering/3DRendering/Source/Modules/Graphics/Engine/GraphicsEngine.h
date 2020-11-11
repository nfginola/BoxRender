#pragma once
#include <memory>

#include "D3D11/D3D11Renderer.h"


namespace Graphics
{
	class GraphicsEngine
	{
	private:
		std::shared_ptr<D3D11Renderer> m_renderer;

		// Eventual batching system that takes in the renderer
		// batchingSystem(m_renderer);
		// ...


	

	public:
		GraphicsEngine(const HWND& hwnd, const int& clientWidth, const int& clientHeight);
		~GraphicsEngine();

		void render(float dt);

	};
}

