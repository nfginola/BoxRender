#pragma once
#include "IShader.h"

class DomainShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_shader;

public:
	DomainShader(Microsoft::WRL::ComPtr<ID3D11DomainShader> shader, DeviceContextPtr devCon);
	~DomainShader();

	virtual void bind() override;
	virtual void bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count) override;
	virtual void bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count) override;
	virtual void bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count) override;

};

