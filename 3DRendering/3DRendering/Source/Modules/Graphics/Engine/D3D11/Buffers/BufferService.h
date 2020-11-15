#pragma once
#include <map>
#include <string>
#include <memory>

#include "Buffer.h"

namespace Graphics
{
	enum class BufferType
	{
		VERTEX_BUFFER,
		INDEX_BUFFER,
		CONSTANT_BUFFER,
		STRUCTURED_BUFFER,
		NOT_USED
	};

	class BufferService
	{
	private:
		std::map<std::string, std::shared_ptr<Buffer>> m_repo;
		DevicePtr m_dev;
		DeviceContextPtr m_devCon;

	private:
		friend class D3D11Renderer;	 // For initialization
		void addDev(DevicePtr dev);
		void addDevCon(DeviceContextPtr devCon);

		std::shared_ptr<Buffer> createBuffer(CD3D11_BUFFER_DESC desc, void* initData);


	public:
		static BufferService& getInstance()
		{
			static BufferService instance;
			return instance;
		};

		BufferService();
		~BufferService();
		BufferService(const BufferService&) = delete;


		bool doesBufferExist(const std::string& name);
		std::string createBuffer(BufferType type, CD3D11_BUFFER_DESC desc, void* initData, std::string name);
		std::shared_ptr<Buffer> getBuffer(std::string name);
		void removeBuffer(std::string name);

	};
}


