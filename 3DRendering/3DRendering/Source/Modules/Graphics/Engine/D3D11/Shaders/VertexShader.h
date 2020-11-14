#pragma once
#include "IShader.h"

class VertexShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:
	VertexShader(Microsoft::WRL::ComPtr<ID3D11VertexShader> shader, DeviceContextPtr devCon, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout);
	~VertexShader();

	virtual void bind() override;
	virtual void bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count) override;
	virtual void bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count) override;
	virtual void bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count) override;


};

