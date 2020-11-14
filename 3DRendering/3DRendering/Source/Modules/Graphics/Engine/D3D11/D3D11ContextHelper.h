#pragma once
#include "DeviceManager/D3D11DeviceManager.h"
#include "Shaders/IShader.h"

namespace Graphics
{
	class D3D11ContextHelper
	{
	private:
		DeviceContextPtr m_devCon;

	public:
		D3D11ContextHelper(DeviceContextPtr devCon);
		~D3D11ContextHelper();

		void clearScreen(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv, float r, float g, float b);
		void unbindShader(ShaderType type);
		void unbindConstantBuffers(ShaderType type, std::uint8_t startSlot = 0, std::uint8_t count = D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT);
		void unbindShaderResources(ShaderType type, std::uint8_t startSlot = 0, std::uint8_t count = D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT);
		void unbindSamplers(ShaderType type, std::uint8_t startSlot = 0, std::uint8_t count = D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT);

	};
}


