#pragma once
#include "IShader.h"

class ComputeShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_shader;

public:
	ComputeShader(Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader, DeviceContextPtr devCon);
	~ComputeShader();

	virtual void bind() override;
	virtual void bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count) override;
	virtual void bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count) override;
	virtual void bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count) override;

};

