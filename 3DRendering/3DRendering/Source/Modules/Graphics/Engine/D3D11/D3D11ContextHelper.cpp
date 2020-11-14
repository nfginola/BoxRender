#include "D3D11ContextHelper.h"

using namespace Graphics;

D3D11ContextHelper::D3D11ContextHelper(DeviceContextPtr devCon) :
	m_devCon(devCon)
{
}

D3D11ContextHelper::~D3D11ContextHelper()
{
}

void D3D11ContextHelper::clearScreen(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv, float r, float g, float b)
{
	if (r > 255.f) r = 255.f;
	if (g > 255.f) g = 255.f;
	if (b > 255.f) b = 255.f;
	const FLOAT color[4] = { r / 255.f, g / 255.f, b / 255.f, 1.f };

	m_devCon->ClearRenderTargetView(rtv.Get(), color);

}

void D3D11ContextHelper::D3D11ContextHelper::unbindShader(ShaderType type)
{
	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		m_devCon->VSSetShader(nullptr, 0, 0);
		break;
	case ShaderType::HULL_SHADER:
		m_devCon->HSSetShader(nullptr, 0, 0);

		break;
	case ShaderType::DOMAIN_SHADER:
		m_devCon->DSSetShader(nullptr, 0, 0);
		break;
	case ShaderType::GEOMETRY_SHADER:
		m_devCon->GSSetShader(nullptr, 0, 0);
		break;
	case ShaderType::PIXEL_SHADER:
		m_devCon->PSSetShader(nullptr, 0, 0);
		break;
	case ShaderType::COMPUTE_SHADER:
		m_devCon->CSSetShader(nullptr, 0, 0);
		break;
	default:
		break;
	}
	return;
}

void Graphics::D3D11ContextHelper::unbindConstantBuffers(ShaderType type, std::uint8_t startSlot, std::uint8_t count)
{
	ID3D11Buffer* nullBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_HW_SLOT_COUNT] = { 0 };

	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		m_devCon->VSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	case ShaderType::HULL_SHADER:
		m_devCon->HSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	case ShaderType::DOMAIN_SHADER:
		m_devCon->DSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	case ShaderType::GEOMETRY_SHADER:
		m_devCon->GSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	case ShaderType::PIXEL_SHADER:
		m_devCon->PSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	case ShaderType::COMPUTE_SHADER:
		m_devCon->CSSetConstantBuffers(startSlot, count, nullBuffers);
		break;
	default:
		break;
	}
	return;

}

void Graphics::D3D11ContextHelper::unbindShaderResources(ShaderType type, std::uint8_t startSlot, std::uint8_t count)
{
	ID3D11ShaderResourceView* nullViews[D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT] = { 0 };

	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		m_devCon->VSSetShaderResources(startSlot, count, nullViews);
		break;
	case ShaderType::HULL_SHADER:
		m_devCon->HSSetShaderResources(startSlot, count, nullViews);
		break;
	case ShaderType::DOMAIN_SHADER:
		m_devCon->DSSetShaderResources(startSlot, count, nullViews);
		break;
	case ShaderType::GEOMETRY_SHADER:
		m_devCon->GSSetShaderResources(startSlot, count, nullViews);
		break;
	case ShaderType::PIXEL_SHADER:
		m_devCon->PSSetShaderResources(startSlot, count, nullViews);
		break;
	case ShaderType::COMPUTE_SHADER:
		m_devCon->CSSetShaderResources(startSlot, count, nullViews);
		break;
	default:
		break;
	}
	return;

}

void Graphics::D3D11ContextHelper::unbindSamplers(ShaderType type, std::uint8_t startSlot, std::uint8_t count)
{
	ID3D11SamplerState* nullSamplers[D3D11_COMMONSHADER_INPUT_RESOURCE_REGISTER_COUNT] = { 0 };

	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		m_devCon->VSSetSamplers(startSlot, count, nullSamplers);
		break;
	case ShaderType::HULL_SHADER:
		m_devCon->HSSetSamplers(startSlot, count, nullSamplers);
		break;
	case ShaderType::DOMAIN_SHADER:
		m_devCon->DSSetSamplers(startSlot, count, nullSamplers);
		break;
	case ShaderType::GEOMETRY_SHADER:
		m_devCon->GSSetSamplers(startSlot, count, nullSamplers);
		break;
	case ShaderType::PIXEL_SHADER:
		m_devCon->PSSetSamplers(startSlot, count, nullSamplers);
		break;
	case ShaderType::COMPUTE_SHADER:
		m_devCon->CSSetSamplers(startSlot, count, nullSamplers);
		break;
	default:
		break;
	}
	return;

}
