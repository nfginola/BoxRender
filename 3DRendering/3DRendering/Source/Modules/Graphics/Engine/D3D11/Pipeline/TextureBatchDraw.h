#pragma once
#include "../D3D11Renderer.h"
#include "../Mesh/Mesh.h"
#include <string>
#include <vector>
#include <utility>

namespace Graphics
{
	class TextureBatchDraw
	{
	private:
		std::shared_ptr<D3D11DeviceManager> m_devMan;
		std::shared_ptr<D3D11ContextHelper> m_devConHelper;
		
		// temp
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pointSampler;

	public:
		TextureBatchDraw(std::shared_ptr<D3D11DeviceManager> devMan, std::shared_ptr<D3D11ContextHelper> devConHelper);
		~TextureBatchDraw();

		void draw(const std::vector<std::shared_ptr<Mesh>>& meshes, const DirectX::SimpleMath::Matrix& camViewMatrix);
	};
}


