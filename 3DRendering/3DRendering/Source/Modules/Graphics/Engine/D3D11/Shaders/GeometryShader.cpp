#include "GeometryShader.h"

GeometryShader::GeometryShader(Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader, DeviceContextPtr devCon) :
	IShader::IShader(devCon),
	m_shader(shader)
{
}

GeometryShader::~GeometryShader()
{
}

void GeometryShader::bind()
{
	m_devCon->GSSetShader(m_shader.Get(), NULL, NULL);
}

void GeometryShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);

	m_devCon->GSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());

	IShader::clearBuffers();
}

void GeometryShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);

	m_devCon->VSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());

	IShader::clearResources();
}

void GeometryShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->GSSetSamplers(startSlot, count, m_samplersIntermediary.data());

	IShader::clearSamplers();
}
