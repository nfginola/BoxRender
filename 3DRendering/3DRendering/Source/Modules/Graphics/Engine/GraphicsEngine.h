#pragma once
#include <memory>

#include "D3D11/D3D11Renderer.h"

class Scene;

namespace Graphics
{
	class GraphicsEngine
	{
	private:
		std::shared_ptr<D3D11Renderer> m_renderer;
		std::shared_ptr<Scene> m_activeScene;

		// Scene
		// 
		// cameras.. (just data)
		// model loader

	public:
		GraphicsEngine(const HWND& hwnd, const int& clientWidth, const int& clientHeight);
		~GraphicsEngine();

		void render(float dt);

		void setScene(std::shared_ptr<Scene> scene);

	};
}


