#include "Buffer.h"

using namespace Graphics;



Buffer::Buffer(DeviceContextPtr devCon, Microsoft::WRL::ComPtr<ID3D11Buffer> buffer) :
	m_devCon(devCon),
	m_buffer(buffer)
{
}

Buffer::~Buffer()
{
}

Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer::getBuffer()
{
	return m_buffer;
}

void Graphics::Buffer::updateBufferMap(void* data, unsigned int dataSize, D3D11_MAP mapType)
{
	D3D11_MAPPED_SUBRESOURCE subres;
	HRESULT hr = m_devCon->Map(m_buffer.Get(), 0, mapType, 0, &subres);

	std::memcpy(subres.pData, data, dataSize);

	m_devCon->Unmap(m_buffer.Get(), 0);
}

// TO IMPLEMENT
void Graphics::Buffer::updateBufferSubres(void* data, unsigned int dataSize)
{
	// TO IMPLEMENT
}


