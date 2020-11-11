#include "PixelShader.h"

PixelShader::PixelShader(Microsoft::WRL::ComPtr<ID3D11PixelShader> shader) :
	m_shader(shader)
{

}

PixelShader::~PixelShader()
{
}

void PixelShader::bind(DeviceContextPtr devCon)
{
	devCon->PSSetShader(m_shader.Get(), NULL, NULL);
}

void PixelShader::unbind(DeviceContextPtr devCon)
{
	devCon->PSSetShader(nullptr, NULL, NULL);
}
