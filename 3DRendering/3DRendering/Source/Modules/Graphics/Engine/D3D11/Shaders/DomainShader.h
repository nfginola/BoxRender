#pragma once
#include "IShader.h"

class DomainShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_shader;

public:
	DomainShader(Microsoft::WRL::ComPtr<ID3D11DomainShader> shader);
	~DomainShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;

};

