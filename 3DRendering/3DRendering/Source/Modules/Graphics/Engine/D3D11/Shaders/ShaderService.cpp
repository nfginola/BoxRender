#include "ShaderService.h"
#include <assert.h>

using namespace D3D11Utilities;
using namespace Graphics;

std::shared_ptr<IShader> Graphics::ShaderService::createShader(ShaderType type, const std::string& rawData)
{
	std::shared_ptr<IShader> shader;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	Microsoft::WRL::ComPtr<ID3D11DomainShader> ds;
	Microsoft::WRL::ComPtr<ID3D11HullShader> hs;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> gs;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> cs;

	HRESULT hr;

	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		hr = m_dev->CreateVertexShader(rawData.data(), rawData.length(), NULL, vs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<VertexShader>(vs);
		break;
	case ShaderType::HULL_SHADER:
		hr = m_dev->CreateHullShader(rawData.data(), rawData.length(), NULL, hs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<HullShader>(hs);
		break;
	case ShaderType::DOMAIN_SHADER:
		hr = m_dev->CreateDomainShader(rawData.data(), rawData.length(), NULL, ds.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<DomainShader>(ds);
		break;
	case ShaderType::GEOMETRY_SHADER:
		hr = m_dev->CreateGeometryShader(rawData.data(), rawData.length(), NULL, gs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<GeometryShader>(gs);
		break;
	case ShaderType::PIXEL_SHADER:
		hr = m_dev->CreatePixelShader(rawData.data(), rawData.length(), NULL, ps.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<PixelShader>(ps);
		break;
	case ShaderType::COMPUTE_SHADER:
		hr = m_dev->CreateComputeShader(rawData.data(), rawData.length(), NULL, cs.GetAddressOf());
		assert(SUCCEEDED(hr));
		shader = std::make_shared<ComputeShader>(cs);
		break;

	default:
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
}

void Graphics::ShaderService::addDev(DevicePtr dev)
{
	m_dev = dev;
}

std::string ShaderService::addShader(ShaderType type, std::string fileName, std::string shaderName)
{
	if (m_repo.find(shaderName) != m_repo.end())
	{
		assert(false);
		return "";
	}

	if (m_dev.Get() == nullptr)
	{
		assert(false);
		return shaderName;
	}

	std::string rawData = loadShader(type, m_compiledShaderDir + fileName);
	std::shared_ptr<IShader> shader = createShader(type, rawData);

	m_repo.insert({ shaderName, shader });

	return shaderName;

}

void ShaderService::removeShader(std::string name)
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

std::shared_ptr<IShader> Graphics::ShaderService::getShader(std::string shaderName)
{
	auto element = m_repo.find(shaderName);
	if (element == m_repo.end())
	{
		return std::shared_ptr<IShader>();
	}

	return element->second;
}
