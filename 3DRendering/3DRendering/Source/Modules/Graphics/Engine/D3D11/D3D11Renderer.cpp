#include "D3D11Renderer.h"

Graphics::D3D11Renderer::D3D11Renderer(const HWND& hwnd, const int& clientWidth, const int& clientHeight)
{
	m_devMan = std::make_unique<D3D11DeviceManager>(hwnd, clientWidth, clientHeight);
	m_devConHelper = std::make_shared<D3D11ContextHelper>(m_devMan->getDeviceContext());

	// Initialize shader service
	ShaderService& shdServ = ShaderService::getInstance();
	shdServ.addDev(m_devMan->getDevice());
	shdServ.addDevCon(m_devMan->getDeviceContext());
	
	BufferService& bufServ = BufferService::getInstance();
	bufServ.addDev(m_devMan->getDevice());
	bufServ.addDevCon(m_devMan->getDeviceContext());


	// Testing -- Should be used in classes that encapsulate techniques
	std::vector<D3D11_INPUT_ELEMENT_DESC> ilDesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shdServ.addVertexShader("VertexShader.cso", "vs", ilDesc);
	shdServ.addShader(ShaderType::PIXEL_SHADER, "PixelShader.cso", "ps");

	shdServ.getShader("vs")->bind();
	shdServ.getShader("ps")->bind();

	struct testData
	{
		float a, b, c, d;
	};

	testData myDat = { 1.f, 1.f, 0.f, 1.f };

	bufServ.createBuffer(
		BufferType::CONSTANT_BUFFER,
		CD3D11_BUFFER_DESC(sizeof(myDat), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
		&myDat, "testCB"
	);

	bufServ.createBuffer(
		BufferType::CONSTANT_BUFFER,
		CD3D11_BUFFER_DESC(sizeof(D3D11Utilities::CBufferAlwaysChanging), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
		nullptr, "alwaysChangingCB"
	);

	// Should have Deafult and no CPU access! (update via subresource)
	bufServ.createBuffer(
		BufferType::CONSTANT_BUFFER,
		CD3D11_BUFFER_DESC(sizeof(D3D11Utilities::CBufferSometimesChanging), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
		nullptr, "sometimesChangingCB"
	);

	m_devMan->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_devMan->getDeviceContext()->RSSetViewports(1, &m_devMan->getVP());

	std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> cbs = 
	{	bufServ.getBuffer("testCB")->getBuffer(), 
		bufServ.getBuffer("alwaysChangingCB")->getBuffer(),
		bufServ.getBuffer("sometimesChangingCB")->getBuffer() 
	};
	shdServ.getShader("vs")->bind();
	shdServ.getShader("ps")->bind();
	shdServ.getShader("vs")->bindConstantBuffers(0, cbs, cbs.size());
	shdServ.getShader("ps")->bindConstantBuffers(0, cbs, 1);

}

Graphics::D3D11Renderer::~D3D11Renderer()
{

}

void Graphics::D3D11Renderer::clearScreen(float r, float g, float b)
{
	m_devConHelper->clearScreen(m_devMan->getRTV(), r, g, b);
}

void Graphics::D3D11Renderer::present()
{
	m_devMan->getSwapChain()->Present(0, 0);
}


void Graphics::D3D11Renderer::tempDraw(std::shared_ptr<Scene> scene)
{
	const DeviceContextPtr& devCon = m_devMan->getDeviceContext();
	BufferService& bufServ = BufferService::getInstance();
	const std::vector<std::shared_ptr<Camera>>& cameras = scene->getCameras();
	const std::vector<std::shared_ptr<Mesh>>& meshes = scene->getMeshes();

	m_devMan->getDeviceContext()->OMSetRenderTargets(1, m_devMan->getRTV().GetAddressOf(), 0); // have to continually set


	// Update buffer
	D3D11Utilities::CBufferSometimesChanging cbSC = { cameras[0]->getProjectionMatrix() };
	bufServ.getBuffer("sometimesChangingCB")->updateBufferMap(&cbSC, sizeof(cbSC), D3D11_MAP_WRITE_DISCARD);

	int x = 0;
	for (const auto& mesh : meshes)
	{
		// Update buffer
		D3D11Utilities::CBufferAlwaysChanging cbAC = { mesh->getWorldMatrix(), cameras[0]->getViewMatrix() };
		bufServ.getBuffer("alwaysChangingCB")->updateBufferMap(&cbAC, sizeof(cbAC), D3D11_MAP_WRITE_DISCARD);

		const std::string& vboID = mesh->getVBOID();
		const std::string& iboID = mesh->getIBOID();
		
		UINT strides[1] = { sizeof(Mesh::Vertex) };
		UINT offsets[1] = { 0 };

		Microsoft::WRL::ComPtr<ID3D11Buffer> vbo = bufServ.getBuffer(vboID)->getBuffer();
		Microsoft::WRL::ComPtr<ID3D11Buffer> ibo = bufServ.getBuffer(iboID)->getBuffer();

		devCon->IASetVertexBuffers(0, 1, vbo.GetAddressOf(), strides, offsets);
		devCon->IASetIndexBuffer(ibo.Get(), DXGI_FORMAT_R32_UINT, 0);

		const std::vector<Mesh::Subset>& subsets = mesh->getSubsets();
		float i = 0;
		for (const auto& subset : subsets)
		{
			if (x == 0)
			{
				struct testData
				{
					float a, b, c, d;
				};

				testData ha = { (float)i / 7.f, 0.f, 0.f, 1.f };
				bufServ.getBuffer("testCB")->updateBufferMap(&ha, sizeof(ha), D3D11_MAP_WRITE_DISCARD);
			}
			else
			{
				struct testData
				{
					float a, b, c, d;
				};

				testData ha = { 0.f, i / 400.f, 0.f, 1.f };
				bufServ.getBuffer("testCB")->updateBufferMap(&ha, sizeof(ha), D3D11_MAP_WRITE_DISCARD);
			}
			

			i++;
			devCon->DrawIndexed(subset.m_indexCount, subset.m_indexStart, subset.m_vertexStart);
		}

		++x;
	}


}
