#pragma once
#include "IShader.h"

class HullShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_shader;

public:
	HullShader(Microsoft::WRL::ComPtr<ID3D11HullShader> shader);
	~HullShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;

};


