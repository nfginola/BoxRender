#include <fstream>
#include <iostream>
#include <assert.h>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "D3D11Utilities.h"
#include "../../ModelLoader/AssimpModelLoader.h"


namespace D3D11Utilities
{
	std::string D3D11Utilities::loadShader(std::string fileName)
	{
		std::string data;
		std::ifstream fileStream;
		fileStream.open(fileName.c_str(), std::ios_base::binary);

		if (fileStream.fail())
		{
			OutputDebugStringW(L"Failed to read file or can't find file!");
			assert(false);
		}

		// reserve memory once
		fileStream.seekg(0, fileStream.end);
		int length = static_cast<int>(fileStream.tellg());
		data.reserve(length);

		fileStream.seekg(0, fileStream.beg);	// place back at beginning
		// copy binary data to string
		data.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());

		fileStream.close();

		return data;
	}


	TextureData loadTextureData(std::string fileName)
	{
		TextureData textData = { };
		unsigned char* data = stbi_load(fileName.c_str(), &textData.width, &textData.height, &textData.channels, STBI_rgb_alpha);

		textData.data = calloc(textData.width * textData.height, sizeof(std::uint32_t));
		std::memcpy(textData.data, data, textData.width * textData.height * sizeof(std::uint32_t));

		stbi_image_free(data);

		return textData;
	}


}

//std::shared_ptr<Mesh> D3D11Utilities::loadMesh(const std::string& filePath, const std::string& meshID)
//{
//	// Prepare services
//	static std::unique_ptr<ModelLoader::IModelLoader> loader = std::make_unique<ModelLoader::AssimpModelLoader>();
//	Graphics::BufferService& bufService = Graphics::BufferService::getInstance();
//
//	std::string vboID = meshID + "_vbo";
//	std::string iboID = meshID + "_ibo";
//
//	// Load mesh
//	ModelLoader::IModelLoader::EngineMeshData modelData = loader->loadStaticModel(filePath);
//
//	// Create VBO and IBO
//	bufService.createBuffer(
//		Graphics::BufferType::NOT_USED,
//		CD3D11_BUFFER_DESC(
//			sizeof(ModelLoader::IModelLoader::Vertex) * modelData.m_vertices.size(),
//			D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE), modelData.m_vertices.data(), vboID);
//
//	bufService.createBuffer(
//		Graphics::BufferType::NOT_USED,
//		CD3D11_BUFFER_DESC(
//			sizeof(ModelLoader::IModelLoader::Vertex) * modelData.m_vertices.size(),
//			D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE), modelData.m_vertices.data(), vboID);
//
//	// Convert to mesh subset
//	std::vector<Mesh::Subset> subsets;
//	subsets.reserve(modelData.m_subsetsInfo.size());
//	for (const auto& modelSubset : modelData.m_subsetsInfo)
//	{
//		Mesh::Subset subset;
//		subset.m_indexStart = modelSubset.m_indexStart;
//		subset.m_indexCount = modelSubset.m_indexCount;
//		subset.m_vertexStart = modelSubset.m_vertexStart;
//		
//		subset.diffuseID = "default";
//
//		subsets.push_back(subset);
//	}
//
//	return std::make_shared<Mesh>(vboID, iboID, subsets);
//}
