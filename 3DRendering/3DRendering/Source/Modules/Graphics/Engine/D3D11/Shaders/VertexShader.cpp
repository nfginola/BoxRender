#include "VertexShader.h"

VertexShader::VertexShader(Microsoft::WRL::ComPtr<ID3D11VertexShader> shader) :
	m_shader(shader)
{

}

VertexShader::~VertexShader()
{
}

void VertexShader::bind(DeviceContextPtr devCon)
{
	devCon->VSSetShader(m_shader.Get(), NULL, NULL);
}

void VertexShader::unbind(DeviceContextPtr devCon)
{
	devCon->VSSetShader(nullptr, NULL, NULL);
}
