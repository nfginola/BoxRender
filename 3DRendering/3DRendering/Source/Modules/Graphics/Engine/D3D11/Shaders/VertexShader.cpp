#include "VertexShader.h"

VertexShader::VertexShader(Microsoft::WRL::ComPtr<ID3D11VertexShader> shader, DeviceContextPtr devCon, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout) :
	IShader::IShader(devCon),
	m_shader(shader),
	m_inputLayout(inputLayout)
{

}

VertexShader::~VertexShader()
{
}

void VertexShader::bind()
{
	m_devCon->IASetInputLayout(m_inputLayout.Get());
	m_devCon->VSSetShader(m_shader.Get(), NULL, NULL);
}

void VertexShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);
	
	m_devCon->VSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());
}

void VertexShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);
	m_devCon->VSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());
}
	

void VertexShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->VSSetSamplers(startSlot, count, m_samplersIntermediary.data());
}
