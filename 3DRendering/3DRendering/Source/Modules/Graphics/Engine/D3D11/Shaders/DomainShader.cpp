#include "DomainShader.h"

DomainShader::DomainShader(Microsoft::WRL::ComPtr<ID3D11DomainShader> shader) :
	m_shader(shader)
{
}

DomainShader::~DomainShader()
{
}

void DomainShader::bind(DeviceContextPtr devCon)
{
	devCon->DSSetShader(m_shader.Get(), NULL, NULL);
}

void DomainShader::unbind(DeviceContextPtr devCon)
{
	devCon->DSSetShader(nullptr, NULL, NULL);
}
