#pragma once
#include "IShader.h"

class HullShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_shader;

public:
	HullShader(Microsoft::WRL::ComPtr<ID3D11HullShader> shader, DeviceContextPtr devCon);
	~HullShader();

	virtual void bind() override;
	virtual void bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count) override;
	virtual void bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count) override;
	virtual void bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count) override;
};


