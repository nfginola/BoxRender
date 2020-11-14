#include "LoaderUtility.h"

std::shared_ptr<Mesh> ModelLoader::loadMesh(const std::string& filePath, const std::string& meshID)
{
	// Prepare services
	std::unique_ptr<ModelLoader::IModelLoader> loader = std::make_unique<ModelLoader::AssimpModelLoader>();
	Graphics::BufferService& bufService = Graphics::BufferService::getInstance();

	std::string vboID = meshID + "_VBO";
	std::string iboID = meshID + "_IBO";

	// Load mesh
	ModelLoader::IModelLoader::EngineMeshData modelData = loader->loadStaticModel(filePath);

	// Create VBO and IBO
	bufService.createBuffer(
		Graphics::BufferType::NOT_USED,
		CD3D11_BUFFER_DESC(
			sizeof(Mesh::Vertex) * modelData.m_vertices.size(),
			D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE), modelData.m_vertices.data(), vboID);

	bufService.createBuffer(
		Graphics::BufferType::NOT_USED,
		CD3D11_BUFFER_DESC(
			sizeof(unsigned int) * modelData.m_indices.size(),
			D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_IMMUTABLE), modelData.m_indices.data(), iboID);

	// Convert to mesh subset
	std::vector<Mesh::Subset> subsets;
	subsets.reserve(modelData.m_subsetsInfo.size());
	for (const auto& modelSubset : modelData.m_subsetsInfo)
	{
		Mesh::Subset subset;
		subset.m_indexStart = modelSubset.m_indexStart;
		subset.m_indexCount = modelSubset.m_indexCount;
		subset.m_vertexStart = modelSubset.m_vertexStart;

		subset.diffuseID = "default";

		subsets.push_back(subset);
	}

	return std::make_shared<Mesh>(vboID, iboID, subsets);
}

