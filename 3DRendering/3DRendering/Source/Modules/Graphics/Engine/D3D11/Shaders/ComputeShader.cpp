#include "ComputeShader.h"

ComputeShader::ComputeShader(Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader) :
	m_shader(shader)
{
}

ComputeShader::~ComputeShader()
{
}

void ComputeShader::bind(DeviceContextPtr devCon)
{
	devCon->CSSetShader(m_shader.Get(), NULL, NULL);
}

void ComputeShader::unbind(DeviceContextPtr devCon)
{
	devCon->CSSetShader(nullptr, NULL, NULL);
}
