#include "HullShader.h"

HullShader::HullShader(Microsoft::WRL::ComPtr<ID3D11HullShader> shader, DeviceContextPtr devCon) :
	IShader::IShader(devCon),
	m_shader(shader)
{
}

HullShader::~HullShader()
{
}

void HullShader::bind()
{
	m_devCon->HSSetShader(m_shader.Get(), NULL, NULL);
}

void HullShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);

	m_devCon->HSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());
}

void HullShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);

	m_devCon->PSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());
}

void HullShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->HSSetSamplers(startSlot, count, m_samplersIntermediary.data());
}
