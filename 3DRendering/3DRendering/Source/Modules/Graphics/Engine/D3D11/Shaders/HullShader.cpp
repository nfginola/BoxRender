#include "HullShader.h"

HullShader::HullShader(Microsoft::WRL::ComPtr<ID3D11HullShader> shader) :
	m_shader(shader)
{
}

HullShader::~HullShader()
{
}

void HullShader::bind(DeviceContextPtr devCon)
{
	devCon->HSSetShader(m_shader.Get(), NULL, NULL);
}

void HullShader::unbind(DeviceContextPtr devCon)
{
	devCon->HSSetShader(nullptr, NULL, NULL);
}
