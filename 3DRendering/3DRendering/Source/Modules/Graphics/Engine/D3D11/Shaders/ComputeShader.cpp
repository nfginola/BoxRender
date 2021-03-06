#include "ComputeShader.h"

ComputeShader::ComputeShader(Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader, DeviceContextPtr devCon) :
	IShader::IShader(devCon),
	m_shader(shader)
{
}

ComputeShader::~ComputeShader()
{
}

void ComputeShader::bind()
{
	m_devCon->CSSetShader(m_shader.Get(), NULL, NULL);
}

void ComputeShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);

	m_devCon->CSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());
	
	IShader::clearBuffers();
}

void ComputeShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);

	m_devCon->VSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());
	
	IShader::clearResources();
}

void ComputeShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->CSSetSamplers(startSlot, count, m_samplersIntermediary.data());
	IShader::clearSamplers();
}

