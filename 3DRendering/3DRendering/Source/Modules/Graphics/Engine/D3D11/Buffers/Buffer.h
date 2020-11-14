#pragma once

#include "../DeviceManager/D3D11DeviceManager.h"
#include <cstring>

namespace Graphics
{
	class Buffer
	{
	public:


	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
		DeviceContextPtr m_devCon;

	public:
		Buffer(DeviceContextPtr devCon, Microsoft::WRL::ComPtr<ID3D11Buffer> buffer);
		~Buffer();

		Microsoft::WRL::ComPtr<ID3D11Buffer> getBuffer();
		void updateBufferMap(void* data, unsigned int dataSize, D3D11_MAP mapType);
		void updateBufferSubres(void* data, unsigned int dataSize);

	};

}


