#include "GeometryShader.h"

GeometryShader::GeometryShader(Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader) :
	m_shader(shader)
{
}

GeometryShader::~GeometryShader()
{
}

void GeometryShader::bind(DeviceContextPtr devCon)
{
	devCon->GSSetShader(m_shader.Get(), NULL, NULL);
}

void GeometryShader::unbind(DeviceContextPtr devCon)
{
	devCon->GSSetShader(nullptr, NULL, NULL);

}
