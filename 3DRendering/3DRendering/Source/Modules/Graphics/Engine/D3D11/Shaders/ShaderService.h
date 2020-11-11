#pragma once

#include <map>
#include <memory>
#include <string>

#include "VertexShader.h"
#include "HullShader.h"
#include "DomainShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "ComputeShader.h"
#include "../DeviceManager/D3D11DeviceManager.h"
#include "../D3D11Renderer.h"

namespace Graphics
{

	class ShaderService
	{
	private:
		const std::string m_compiledShaderDir;
		std::map<std::string, std::shared_ptr<IShader>> m_repo;
		DevicePtr m_dev;

	private:
		friend class D3D11Renderer;	 // For initialization
		void addDev(DevicePtr dev);

		std::shared_ptr<IShader> createShader(ShaderType type, const std::string& rawData);

	public:
		static ShaderService& getInstance()
		{
			static ShaderService instance;
			return instance;
		};

	public:

		ShaderService();
		~ShaderService();
		ShaderService(const ShaderService&) = delete;


		std::string addShader(ShaderType type, std::string fileName, std::string shaderName);
		void removeShader(std::string name);
		std::shared_ptr<IShader> getShader(std::string shaderName);



	};
}


