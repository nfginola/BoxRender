#include "D3D11Renderer.h"

Graphics::D3D11Renderer::D3D11Renderer(const HWND& hwnd, const int& clientWidth, const int& clientHeight)
{
	m_devMan = std::make_shared<D3D11DeviceManager>(hwnd, clientWidth, clientHeight);
	m_devConHelper = std::make_shared<D3D11ContextHelper>(m_devMan->getDeviceContext());

	// Initialize services
	ShaderService& shdServ = ShaderService::getInstance();
	shdServ.addDev(m_devMan->getDevice());
	shdServ.addDevCon(m_devMan->getDeviceContext());
	
	BufferService& bufServ = BufferService::getInstance();
	bufServ.addDev(m_devMan->getDevice());
	bufServ.addDevCon(m_devMan->getDeviceContext());

	TextureService& texSrv = TextureService::getInstance();
	texSrv.addDev(m_devMan->getDevice());




	// Testing -- Should be used in classes that encapsulate techniques
	std::vector<D3D11_INPUT_ELEMENT_DESC> ilDesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shdServ.addVertexShader("VertexShader.cso", "vs", ilDesc);
	shdServ.addShader(ShaderType::PIXEL_SHADER, "PixelShader.cso", "ps");

	// Line renderer
	shdServ.addVertexShader("LineVS.cso", "lineVS", { });
	shdServ.addShader(ShaderType::GEOMETRY_SHADER, "LineGS.cso", "lineGS");
	shdServ.addShader(ShaderType::PIXEL_SHADER, "LinePS.cso", "linePS");

	//shdServ.getShader("vs")->bind();
	//shdServ.getShader("ps")->bind();

	struct testData
	{
		float a, b, c, d;
	};

	struct aabbDat
	{
		DirectX::XMFLOAT4 center;
		float x, y, z;
		DirectX::XMMATRIX rotationMatrix;
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

	bufServ.createBuffer(
		BufferType::CONSTANT_BUFFER,
		CD3D11_BUFFER_DESC(sizeof(aabbDat), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE),
		nullptr, "aabbCB"
	);

	//m_devMan->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_devMan->getDeviceContext()->RSSetViewports(1, &m_devMan->getVP());

	//std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> cbs = 
	//{	bufServ.getBuffer("testCB")->getBuffer(), 
	//	bufServ.getBuffer("alwaysChangingCB")->getBuffer(),
	//	bufServ.getBuffer("sometimesChangingCB")->getBuffer() 
	//};
	//shdServ.getShader("vs")->bind();
	//shdServ.getShader("ps")->bind();
	//shdServ.getShader("vs")->bindConstantBuffers(0, cbs, cbs.size());
	//shdServ.getShader("ps")->bindConstantBuffers(0, cbs, 1);

	// Create depth stencil view (enable depth test)
	Microsoft::WRL::ComPtr<ID3D11Texture2D> dsvText;
	D3D11_TEXTURE2D_DESC textDesc = { };
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = { };
	{
		textDesc.Width = clientWidth;
		textDesc.Height = clientHeight;
		textDesc.MipLevels = 0;
		textDesc.ArraySize = 1;
		textDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		textDesc.SampleDesc.Count = 1;
		textDesc.SampleDesc.Quality = 0;
		textDesc.Usage = D3D11_USAGE_DEFAULT;
		textDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		textDesc.CPUAccessFlags = 0;
		textDesc.MiscFlags = 0;

		HRESULT hr = m_devMan->getDevice()->CreateTexture2D(&textDesc, NULL, dsvText.GetAddressOf());
		assert(SUCCEEDED(hr));


		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = 0;
		dsvDesc.Texture2D.MipSlice = 0;					// The index of the first mipmap level to use.

		hr = m_devMan->getDevice()->CreateTexture2D(&textDesc, NULL, dsvText.GetAddressOf());
		assert(SUCCEEDED(hr));
		hr = m_devMan->getDevice()->CreateDepthStencilView(dsvText.Get(), &dsvDesc, m_dsv.GetAddressOf());
		assert(SUCCEEDED(hr));
	}



	// Tech
	m_textureBatchDraw = std::make_shared<TextureBatchDraw>(m_devMan, m_devConHelper);

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
	const std::vector<std::shared_ptr<DirectX::BoundingOrientedBox>>& boundingBoxes = scene->getBoundingBoxes();

	devCon->ClearDepthStencilView(m_dsv.Get(), D3D11_CLEAR_DEPTH, 1.f, 0.f);
	m_devMan->getDeviceContext()->OMSetRenderTargets(1, m_devMan->getRTV().GetAddressOf(), m_dsv.Get()); // have to continually set

	ShaderService& shdServ = ShaderService::getInstance();

	// Update buffer
	D3D11Utilities::CBufferSometimesChanging cbSC = { cameras[0]->getProjectionMatrix() };
	bufServ.getBuffer("sometimesChangingCB")->updateBufferMap(&cbSC, sizeof(cbSC), D3D11_MAP_WRITE_DISCARD);

	// Render object
	{
		m_devMan->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_devMan->getDeviceContext()->RSSetViewports(1, &m_devMan->getVP());


		std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> cbs =
		{
			bufServ.getBuffer("testCB")->getBuffer(),
			bufServ.getBuffer("alwaysChangingCB")->getBuffer(),
			bufServ.getBuffer("sometimesChangingCB")->getBuffer()
		};

		shdServ.getShader("vs")->bind();
		shdServ.getShader("ps")->bind();
		shdServ.getShader("vs")->bindConstantBuffers(0, cbs, cbs.size());
		shdServ.getShader("ps")->bindConstantBuffers(0, cbs, 1);

		m_textureBatchDraw->draw(meshes, cameras[0]->getViewMatrix());
	}

	// Render bounding box
	{
		m_devMan->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_devMan->getDeviceContext()->IASetInputLayout(nullptr);

		shdServ.getShader("lineVS")->bind();
		shdServ.getShader("lineGS")->bind();
		shdServ.getShader("linePS")->bind();
		shdServ.getShader("lineGS")->bindConstantBuffers(0, { bufServ.getBuffer("alwaysChangingCB")->getBuffer(),
				bufServ.getBuffer("sometimesChangingCB")->getBuffer(),
				bufServ.getBuffer("aabbCB")->getBuffer() }, 3);



		struct aabbDat
		{
			DirectX::XMFLOAT4 center;
			float x, y, z;
			DirectX::XMMATRIX rotationMatrix;
		};
		
		for (std::size_t i = 0; i < boundingBoxes.size(); ++i)
		{
			// For each AABB -- Get them down here! (Do it in a separate function called from Graphics! e.g drawAABB)
			D3D11Utilities::CBufferAlwaysChanging cbAC = { meshes[i]->getWorldMatrix(), cameras[0]->getViewMatrix() };
			bufServ.getBuffer("alwaysChangingCB")->updateBufferMap(&cbAC, sizeof(cbAC), D3D11_MAP_WRITE_DISCARD);

			aabbDat dat = { DirectX::XMFLOAT4(boundingBoxes[i]->Center.x, boundingBoxes[i]->Center.y, boundingBoxes[i]->Center.z, 1.f), 
							boundingBoxes[i]->Extents.x, boundingBoxes[i]->Extents.y, boundingBoxes[i]->Extents.z,
							DirectX::SimpleMath::Matrix::CreateFromQuaternion(boundingBoxes[i]->Orientation)};
			bufServ.getBuffer("aabbCB")->updateBufferMap(&dat, sizeof(dat), D3D11_MAP_WRITE_DISCARD);
			m_devMan->getDeviceContext()->Draw(1, 0);
		}

		m_devConHelper->unbindShader(ShaderType::VERTEX_SHADER);
		m_devConHelper->unbindShader(ShaderType::GEOMETRY_SHADER);
		m_devConHelper->unbindShader(ShaderType::PIXEL_SHADER);

	}




}
