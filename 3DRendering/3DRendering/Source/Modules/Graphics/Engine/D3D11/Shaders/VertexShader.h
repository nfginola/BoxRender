#pragma once
#include "IShader.h"

class VertexShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader;

public:
	VertexShader(Microsoft::WRL::ComPtr<ID3D11VertexShader> shader);
	~VertexShader();
	void bind(DeviceContextPtr devCon) override;
	void unbind(DeviceContextPtr devCon) override;

};

