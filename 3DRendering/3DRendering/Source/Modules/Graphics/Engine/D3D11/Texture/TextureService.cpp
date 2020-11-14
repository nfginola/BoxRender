#include "TextureService.h"

Graphics::TextureService::TextureService()
{
}

Graphics::TextureService::~TextureService()
{
}

std::string Graphics::TextureService::addSRV(const std::string& fileName, const std::string& id)
{
	if (m_dev == nullptr)
	{
		assert(false);
		return "";
	}

	const auto& el = m_srvRepo.find(id);

	// texture already exist, return material name
	if (el != m_srvRepo.end())
	{
		return el->first;
	}



	D3D11Utilities::TextureData textureData = D3D11Utilities::loadTextureData(fileName);

	// Create texture2D
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
	D3D11_TEXTURE2D_DESC tex2DDesc = CD3D11_TEXTURE2D_DESC(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, textureData.width, textureData.height, 1, 1);
	//D3D11_SUBRESOURCE_DATA tex2DSubres = { };

	D3D11_SUBRESOURCE_DATA tex2DSubres = { };
	tex2DSubres.pSysMem = textureData.data;
	tex2DSubres.SysMemPitch = textureData.width * sizeof(uint32_t);
	assert(SUCCEEDED(m_dev->CreateTexture2D(&tex2DDesc, &tex2DSubres, tex2D.GetAddressOf())));
	free(textureData.data);

	// Create SRV
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = CD3D11_SHADER_RESOURCE_VIEW_DESC(D3D11_SRV_DIMENSION_TEXTURE2D, tex2DDesc.Format);
	assert(SUCCEEDED(m_dev->CreateShaderResourceView(tex2D.Get(), &srvDesc, srv.GetAddressOf())));

	m_srvRepo.insert({ id, srv });

	return id;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Graphics::TextureService::getSRV(const std::string& id)
{
	auto element = m_srvRepo.find(id);
	if (element == m_srvRepo.end())
	{
		return nullptr;
	}
	return element->second;
}

void Graphics::TextureService::addDev(DevicePtr dev)
{
	m_dev = dev;
}
