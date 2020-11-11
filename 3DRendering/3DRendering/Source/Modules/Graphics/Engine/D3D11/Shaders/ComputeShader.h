#pragma once
#include "IShader.h"

class ComputeShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_shader;

public:
	ComputeShader(Microsoft::WRL::ComPtr<ID3D11ComputeShader> shader);
	~ComputeShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;

};

