#include "TextureBatchDraw.h"

Graphics::TextureBatchDraw::TextureBatchDraw(std::shared_ptr<D3D11DeviceManager> devMan, std::shared_ptr<D3D11ContextHelper> devConHelper) :
	m_devMan(devMan),
	m_devConHelper(devConHelper)

{
	// Temp sampler (we should have a repo for this)
	D3D11_SAMPLER_DESC samplerDesc = { };
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;									// not used for current filter
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;		// read in detail another time
	samplerDesc.BorderColor[0] = 0.f;
	samplerDesc.BorderColor[1] = 0.f;
	samplerDesc.BorderColor[2] = 0.f;
	samplerDesc.BorderColor[3] = 0.f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;		// no upper limit to LOD selection 

	assert(SUCCEEDED(m_devMan->getDevice()->CreateSamplerState(&samplerDesc, m_pointSampler.GetAddressOf())));

	ShaderService& shdServ = ShaderService::getInstance();
	shdServ.getShader("ps")->bindSamplers(0, { m_pointSampler }, 1);
}

Graphics::TextureBatchDraw::~TextureBatchDraw()
{
}

void Graphics::TextureBatchDraw::draw(const std::vector<std::shared_ptr<Mesh>>& meshes, const DirectX::SimpleMath::Matrix& camViewMatrix)
{
	BufferService& bufServ = BufferService::getInstance();
	ShaderService& shdServ = ShaderService::getInstance();
	TextureService& texServ = TextureService::getInstance();

	for (const auto& mesh : meshes)
	{
		if (mesh->shouldRender())
		{

			D3D11Utilities::CBufferAlwaysChanging cbAC = { mesh->getWorldMatrix(), camViewMatrix };
			bufServ.getBuffer("alwaysChangingCB")->updateBufferMap(&cbAC, sizeof(cbAC), D3D11_MAP_WRITE_DISCARD);

			const std::string& vboID = mesh->getVBOID();
			const std::string& iboID = mesh->getIBOID();

			Microsoft::WRL::ComPtr<ID3D11Buffer> vbo = bufServ.getBuffer(vboID)->getBuffer();
			Microsoft::WRL::ComPtr<ID3D11Buffer> ibo = bufServ.getBuffer(iboID)->getBuffer();

			UINT strides[1] = { sizeof(Mesh::Vertex) };
			UINT offsets[1] = { 0 };
			m_devMan->getDeviceContext()->IASetVertexBuffers(0, 1, vbo.GetAddressOf(), strides, offsets);
			m_devMan->getDeviceContext()->IASetIndexBuffer(ibo.Get(), DXGI_FORMAT_R32_UINT, 0);

			// Get texture batch
			std::map<std::string, std::vector<Mesh::Subset>> matToMesh = mesh->getTextureBatchedSubsets();

			// Render 
			for (const auto& el : matToMesh)
			{
				// Load new texture here
				std::string matName = el.first;
				Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv = texServ.getSRV(matName);
				shdServ.getShader("ps")->bindShaderResources(0, { srv }, 1);

				// Draw all subsets with that texture
				for (const auto& subset : el.second)
				{
					m_devMan->getDeviceContext()->DrawIndexed(subset.m_indexCount, subset.m_indexStart, subset.m_vertexStart);
				}
			}
		}
		


	}

}
