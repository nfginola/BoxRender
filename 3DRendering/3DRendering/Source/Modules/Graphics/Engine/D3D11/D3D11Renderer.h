#pragma once
#include <memory>

#include "DeviceManager/D3D11DeviceManager.h"
#include "Shaders/ShaderService.h"

namespace Graphics
{
	class D3D11Renderer
	{
	private:
		std::unique_ptr<D3D11DeviceManager> m_devMan;

	public:
		D3D11Renderer(const HWND& hwnd, const int& clientWidth, const int& clientHeight);
		~D3D11Renderer();

		void clearScreen(float r, float g, float b);
		void present();
		void bindShader(IShader* shader);
		void unbindShader(IShader* shader);

		// setShader(shaderType, ..)
		// setCamera()

	};
}


