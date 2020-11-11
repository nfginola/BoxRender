#pragma once
#include <string>

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
	std::string loadShader(ShaderType type, std::string fileName);
};
