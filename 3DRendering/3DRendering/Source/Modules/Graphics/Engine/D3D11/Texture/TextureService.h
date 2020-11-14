#pragma once
#include <map>
#include <string>

#include "../DeviceManager/D3D11DeviceManager.h"
#include "../Utilities//D3D11Utilities.h"

namespace Graphics
{
	class TextureService
	{
	private:
		friend class D3D11Renderer;
		void addDev(DevicePtr dev);

		DevicePtr m_dev;

		std::map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_srvRepo;

	public:
		static TextureService& getInstance()
		{
			static TextureService instance;
			return instance;
		};

		TextureService();
		~TextureService();

		std::string addSRV(const std::string& fileName, const std::string& id);
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> getSRV(const std::string& id);


	};
}


