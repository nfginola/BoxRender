#pragma once
#include <memory>
#include <vector>
#include <stdint.h>

#include "../../../Scene/Scene.h"
#include "DeviceManager/D3D11DeviceManager.h"
#include "Shaders/ShaderService.h"
#include "Buffers/BufferService.h"
#include "D3D11ContextHelper.h"
#include "Pipeline/TextureBatchDraw.h"

class TextureBatchDraw;

namespace Graphics
{
	// Our own little API
	class D3D11Renderer
	{
	private:

		std::shared_ptr<D3D11DeviceManager> m_devMan;
		std::shared_ptr<D3D11ContextHelper> m_devConHelper;
		std::shared_ptr<TextureBatchDraw> m_textureBatchDraw;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_dsv;	// temp



	public:
		D3D11Renderer(const HWND& hwnd, const int& clientWidth, const int& clientHeight);
		~D3D11Renderer();

		// abstractions (prototyping..)
		void clearScreen(float r, float g, float b);
		void present();

		// .... deviceContext->Draw(3,0)

		void tempDraw(std::shared_ptr<Scene> scene);
		


		// setShader(shaderType, ..)
		// setCamera()

	};
}


