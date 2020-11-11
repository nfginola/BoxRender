#pragma once
#include "IShader.h"

class VertexShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader;

public:
	VertexShader(Microsoft::WRL::ComPtr<ID3D11VertexShader> shader);
	~VertexShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;

};

