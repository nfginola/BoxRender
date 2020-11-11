#pragma once
#include "IShader.h"

class PixelShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shader;

public:
	PixelShader(Microsoft::WRL::ComPtr<ID3D11PixelShader> shader);
	~PixelShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;


};

