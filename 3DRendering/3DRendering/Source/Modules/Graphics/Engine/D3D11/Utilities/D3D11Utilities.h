#pragma once
#include <string>
#include <memory>
#include <DirectXTK/SimpleMath.h>

#include "../Mesh/Mesh.h"
#include "../Buffers/BufferService.h"

enum class ShaderType
{
	VERTEX_SHADER,
	HULL_SHADER,
	DOMAIN_SHADER,
	GEOMETRY_SHADER,
	PIXEL_SHADER,
	COMPUTE_SHADER,
	NULL_SHADER
};

namespace D3D11Utilities
{
	struct CBufferAlwaysChanging
	{
		DirectX::SimpleMath::Matrix worldMatrix;
		DirectX::SimpleMath::Matrix viewMatrix;
	};

	struct CBufferSometimesChanging
	{
		DirectX::SimpleMath::Matrix projectionMatrix;
	};

	std::string loadShader(std::string fileName);

	//std::shared_ptr<Mesh> loadMesh(const std::string& filePath, const std::string& meshID);
};
