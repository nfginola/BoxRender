#include "IShader.h"

void IShader::gatherConstantBuffers(std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count)
{
	assert(count <= buffers.size());
	for (auto el : buffers)
	{
		m_buffersIntermediary.push_back(el.Get());
	}
}

void IShader::gatherShaderResources(std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count)
{
	assert(count <= resources.size());
	for (auto el : resources)
	{
		m_resourcesIntermediary.push_back(el.Get());
	}
}

void IShader::gatherSamplers(std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count)
{
	assert(count <= samplers.size());
	for (auto el : samplers)
	{
		m_samplersIntermediary.push_back(el.Get());
	}
}

IShader::IShader(DeviceContextPtr devCon) :
	m_devCon(devCon)
{
	m_buffersIntermediary.reserve(D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT);
	m_resourcesIntermediary.reserve(D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT);
	m_samplersIntermediary.reserve(D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT);
}

IShader::~IShader()
{
}
