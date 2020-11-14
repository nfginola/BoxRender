#include "ShaderService.h"
#include <assert.h>

using namespace Graphics;

std::shared_ptr<IShader> Graphics::ShaderService::createShader(ShaderType type, const std::string& rawData)
{
	std::shared_ptr<IShader> shader;

	Microsoft::WRL::ComPtr<ID3D11DomainShader> ds;
	Microsoft::WRL::ComPtr<ID3D11HullShader> hs;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> cs;

	HRESULT hr;

	switch (type)
	{
	//case ShaderType::VERTEX_SHADER:
	//	hr = m_dev->CreateVertexShader(rawData.data(), rawData.length(), NULL, vs.GetAddressOf());
	//	assert(SUCCEEDED(hr));
	//	shader = std::make_shared<VertexShader>(vs, m_devCon, createInputLayout(rawData));
	//	break;
	case ShaderType::HULL_SHADER:
		hr = m_dev->CreateHullShader(rawData.data(), rawData.length(), NULL, hs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<HullShader>(hs, m_devCon);
		break;
	case ShaderType::DOMAIN_SHADER:
		hr = m_dev->CreateDomainShader(rawData.data(), rawData.length(), NULL, ds.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<DomainShader>(ds, m_devCon);
		break;
	case ShaderType::GEOMETRY_SHADER:
		hr = m_dev->CreateGeometryShader(rawData.data(), rawData.length(), NULL, gs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<GeometryShader>(gs, m_devCon);
		break;
	case ShaderType::PIXEL_SHADER:
		hr = m_dev->CreatePixelShader(rawData.data(), rawData.length(), NULL, ps.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<PixelShader>(ps, m_devCon);
		break;
	case ShaderType::COMPUTE_SHADER:
		hr = m_dev->CreateComputeShader(rawData.data(), rawData.length(), NULL, cs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<ComputeShader>(cs, m_devCon);
		break;

	default:
		OutputDebugStringW(L"Use the other function addVertexShader(..) to create a Vertex Shader.");
		assert(false);
		return std::shared_ptr<IShader>();
		break;
	}
	
	return shader;
}

ShaderService::ShaderService() :
	m_compiledShaderDir("Source\\CompiledShaders\\")
{
}

ShaderService::~ShaderService()
{
	m_repo.clear();
}

void Graphics::ShaderService::addDev(DevicePtr dev)
{
	m_dev = dev;
}

void Graphics::ShaderService::addDevCon(DeviceContextPtr devCon)
{
	m_devCon = devCon;
}

std::string ShaderService::addShader(ShaderType type, std::string fileName, std::string shaderName)
{
	if (m_repo.find(shaderName) != m_repo.end())
	{
		// Name already exist!
		assert(false);
		return "";
	}

	if (m_dev.Get() == nullptr || m_devCon.Get() == nullptr)
	{
		assert(false);
		return "";
	}

	std::string rawData = D3D11Utilities::loadShader(m_compiledShaderDir + fileName);
	std::shared_ptr<IShader> shader = createShader(type, rawData);

	m_repo.insert({ shaderName, shader });

	return shaderName;

}

std::string Graphics::ShaderService::addVertexShader(std::string fileName, std::string shaderName, std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc)
{
	if (m_repo.find(shaderName) != m_repo.end())
	{
		// Name already exist!
		assert(false);
		return "";
	}

	if (m_dev.Get() == nullptr || m_devCon.Get() == nullptr)
	{
		assert(false);
		return "";
	}

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	std::string rawData = D3D11Utilities::loadShader(m_compiledShaderDir + fileName);

	HRESULT hr = m_dev->CreateVertexShader(rawData.data(), rawData.length(), NULL, vs.GetAddressOf());
	assert(SUCCEEDED(hr));

	// Create input layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	hr = m_dev->CreateInputLayout(inputLayoutDesc.data(), inputLayoutDesc.size(), rawData.data(), rawData.size(), inputLayout.GetAddressOf());
	assert(SUCCEEDED(hr));

	std::shared_ptr<IShader> shader = std::make_shared<VertexShader>(vs, m_devCon, inputLayout);

	m_repo.insert({ shaderName, shader });

	return shaderName;
}

void ShaderService::removeShader(std::string name)
{
	auto element = m_repo.find(name);
	if (element == m_repo.end())
	{
		return;
	}

	m_repo.erase(element);

}

std::shared_ptr<IShader> Graphics::ShaderService::getShader(std::string shaderName)
{
	auto element = m_repo.find(shaderName);
	if (element == m_repo.end())
	{
		return std::shared_ptr<IShader>();
	}

	return element->second;
}
