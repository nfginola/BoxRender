#include "BufferService.h"

using namespace Graphics;


BufferService::BufferService()
{
}

BufferService::~BufferService()
{
	m_repo.clear();
}

bool Graphics::BufferService::doesBufferExist(const std::string& name)
{
	auto el = m_repo.find(name);
	if (el == m_repo.end())
	{
		return false;
	}
	return true;
}

std::string Graphics::BufferService::createBuffer(BufferType type, CD3D11_BUFFER_DESC desc, void* initData, std::string name)
{
	auto el = m_repo.find(name);
	if (el != m_repo.end())
	{
		// Buffer already exist!
		return name;
	}

	if (m_dev.Get() == nullptr)
	{
		assert(false);
		return "";
	}

	std::shared_ptr<Buffer> buf;

	UINT initialByteWidth = desc.ByteWidth;

	switch (type)
	{
	case BufferType::CONSTANT_BUFFER:
		// Align 16 byte
		desc.ByteWidth = initialByteWidth + (16 - (initialByteWidth % 16));
		buf = createBuffer(desc, initData);
		break;
	default:
		buf = createBuffer(desc, initData);
		break;
	}

	m_repo.insert({ name, buf });
	return name;
}

std::shared_ptr<Buffer> BufferService::getBuffer(std::string name)
{
	auto element = m_repo.find(name);
	if (element == m_repo.end())
	{
		return nullptr;
	}

	return element->second;
}

void BufferService::removeBuffer(std::string name)
{
	if (m_dev.Get() == nullptr)
	{
		assert(false);
	}

	auto element = m_repo.find(name);
	if (element == m_repo.end())
	{
		return;
	}

	m_repo.erase(element);
}


void Graphics::BufferService::addDev(DevicePtr dev)
{
	m_dev = dev;
}

void Graphics::BufferService::addDevCon(DeviceContextPtr devCon)
{
	m_devCon = devCon;
}

std::shared_ptr<Buffer> BufferService::createBuffer(CD3D11_BUFFER_DESC desc, void* initData)
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> bufPtr;

	D3D11_SUBRESOURCE_DATA subresData = { };
	subresData.pSysMem = initData;

	if (initData != nullptr)
		assert(SUCCEEDED(m_dev->CreateBuffer(&desc, &subresData, bufPtr.GetAddressOf())));
	else
		assert(SUCCEEDED(m_dev->CreateBuffer(&desc, 0, bufPtr.GetAddressOf())));

	std::shared_ptr<Buffer> buf = std::make_shared<Buffer>(m_devCon, bufPtr);

	return buf;
}
