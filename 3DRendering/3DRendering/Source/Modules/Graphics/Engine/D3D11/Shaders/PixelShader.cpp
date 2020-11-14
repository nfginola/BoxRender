#include "PixelShader.h"

PixelShader::PixelShader(Microsoft::WRL::ComPtr<ID3D11PixelShader> shader, DeviceContextPtr devCon) :
	IShader::IShader(devCon),
	m_shader(shader)
{

}

PixelShader::~PixelShader()
{
}

void PixelShader::bind()
{
	m_devCon->PSSetShader(m_shader.Get(), NULL, NULL);
}

void PixelShader::bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	IShader::gatherConstantBuffers(buffers, count);

	m_devCon->PSSetConstantBuffers(startSlot, count, m_buffersIntermediary.data());

	IShader::clearBuffers();
}

void PixelShader::bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	IShader::gatherShaderResources(resources, count);

	m_devCon->PSSetShaderResources(startSlot, count, m_resourcesIntermediary.data());

	IShader::clearResources();
}

void PixelShader::bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	IShader::gatherSamplers(samplers, count);

	m_devCon->PSSetSamplers(startSlot, count, m_samplersIntermediary.data());
	
	IShader::clearSamplers();
}
