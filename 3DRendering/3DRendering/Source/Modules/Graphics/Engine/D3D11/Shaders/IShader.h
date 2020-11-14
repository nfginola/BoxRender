#pragma once

#include <vector>
#include <wrl.h>
#include <stdint.h>

#include "../Utilities//D3D11Utilities.h"
#include "../DeviceManager/D3D11DeviceManager.h"

class IShader
{
protected:
	std::vector<ID3D11Buffer*> m_buffersIntermediary;
	std::vector<ID3D11ShaderResourceView*> m_resourcesIntermediary;
	std::vector<ID3D11SamplerState*> m_samplersIntermediary;
	DeviceContextPtr m_devCon;

	void gatherConstantBuffers(std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count);
	void gatherShaderResources(std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count);
	void gatherSamplers(std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count);

public:
	IShader(DeviceContextPtr devCon);
	virtual ~IShader() = 0;

	virtual void bind() = 0;
	virtual void bindConstantBuffers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers, std::uint8_t count) = 0;
	virtual void bindShaderResources(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> resources, std::uint8_t count) = 0;
	virtual void bindSamplers(std::uint8_t startSlot, std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers, std::uint8_t count) = 0;

};

