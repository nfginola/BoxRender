#include "DomainShader.h"

DomainShader::DomainShader(Microsoft::WRL::ComPtr<ID3D11DomainShader> shader, DeviceContextPtr devCon) :
	IShader::IShader(devCon),
	m_shader(shader)
{
}

DomainShader::~DomainShader()
{
}

void DomainShader::bind()
{
	m_devCon->DSSetShader(m_shader.Get(), NULL, NULL);
}

void DomainShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);

	m_devCon->DSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());

	IShader::clearBuffers();
}

void DomainShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);

	m_devCon->VSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());

	IShader::clearResources();
}

void DomainShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->DSSetSamplers(startSlot, count, m_samplersIntermediary.data());

	IShader::clearSamplers();
}
