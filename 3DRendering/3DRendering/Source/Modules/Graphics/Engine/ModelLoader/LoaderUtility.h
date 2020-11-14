#pragma once
#include "../D3D11/Utilities/D3D11Utilities.h"
#include "AssimpModelLoader.h"

namespace ModelLoader
{
	std::shared_ptr<Mesh> loadMesh(const std::string& filePath, const std::string& meshID);
}

