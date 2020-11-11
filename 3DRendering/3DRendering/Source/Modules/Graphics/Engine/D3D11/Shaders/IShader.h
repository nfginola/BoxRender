#pragma once
#include "../Utilities//D3D11Utilities.h"
#include "../DeviceManager/D3D11DeviceManager.h"

#include <wrl.h>

class IShader
{
protected:
	ShaderType m_type;

public:
	IShader();
	~IShader();

	virtual void bind(DeviceContextPtr devCon) = 0;
	virtual void unbind(DeviceContextPtr devCon) = 0;

};

