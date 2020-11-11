#pragma once
#include "IShader.h"

class GeometryShader : public IShader
{
private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_shader;

public:
	GeometryShader(Microsoft::WRL::ComPtr<ID3D11GeometryShader> shader);
	~GeometryShader();
	virtual void bind(DeviceContextPtr devCon) override;
	virtual void unbind(DeviceContextPtr devCon) override;

};
