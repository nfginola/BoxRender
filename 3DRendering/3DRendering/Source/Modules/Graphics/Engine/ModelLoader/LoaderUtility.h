#pragma once
#include "../D3D11/Utilities/D3D11Utilities.h"
#include "../D3D11/Texture//TextureService.h"
#include <DirectXCollision.h>
#include "AssimpModelLoader.h"
#include <filesystem>

namespace ModelLoader
{
	std::shared_ptr<Mesh> loadMesh(const std::string& filePath, const std::string& meshID, DirectX::BoundingOrientedBox& boundingBox);
}

