#pragma once

#include <wrl.h>
#include <stdint.h>

#include "../Utilities//D3D11Utilities.h"
#include "../DeviceManager/D3D11DeviceManager.h"

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

