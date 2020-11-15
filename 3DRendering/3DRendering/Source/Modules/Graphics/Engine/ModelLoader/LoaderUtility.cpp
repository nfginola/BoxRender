#include "LoaderUtility.h"

std::shared_ptr<Mesh> ModelLoader::loadMesh(const std::string& filePath, const std::string& meshID, DirectX::BoundingOrientedBox& boundingBox)
{
	// Prepare services
	std::unique_ptr<ModelLoader::IModelLoader> loader = std::make_unique<ModelLoader::AssimpModelLoader>();
	Graphics::BufferService& bufService = Graphics::BufferService::getInstance();
	Graphics::TextureService& texService = Graphics::TextureService::getInstance();

	std::string vboID = meshID + "_VBO";
	std::string iboID = meshID + "_IBO";


	std::filesystem::path fpath(filePath);
	std::string modelName = fpath.stem().string();
	std::string fpathDir = fpath.parent_path().string() + std::string("\\");		// Get directory of where the file is

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

	// Create list of only positions
	std::vector<DirectX::XMFLOAT3> positions;
	for (const auto& vertex : modelData.m_vertices)
	{
		positions.push_back(DirectX::XMFLOAT3(vertex.m_position.x, vertex.m_position.y, vertex.m_position.z));
	}

	// For some reason, if initialized directly with BoundingOrientedBox, gives wrong extents!
	DirectX::BoundingBox aabb;
	DirectX::BoundingBox::CreateFromPoints(aabb, positions.size(), positions.data(), sizeof(DirectX::XMFLOAT3));

	boundingBox.CreateFromBoundingBox(boundingBox, aabb);

	// Fix orientation??
	//float extentX = boundingBox.Extents.x;
	//float extentY = boundingBox.Extents.y;
	//float extentZ = boundingBox.Extents.z;

	//boundingBox.Extents.y = extentZ;
	//boundingBox.Extents.z = extentX;
	//boundingBox.Extents.x = extentZ;

	// Convert to mesh subset
	std::vector<Mesh::Subset> subsets;
	subsets.reserve(modelData.m_subsetsInfo.size());
	for (const auto& modelSubset : modelData.m_subsetsInfo)
	{
		Mesh::Subset subset;
		subset.m_indexStart = modelSubset.m_indexStart;
		subset.m_indexCount = modelSubset.m_indexCount;
		subset.m_vertexStart = modelSubset.m_vertexStart;

		// Get material name
		std::filesystem::path matPath(modelSubset.m_diffuseFilePath);
		std::string materialName = matPath.stem().string();
		std::string finalTexturePath = fpathDir + modelSubset.m_diffuseFilePath;

		if (materialName.empty())
		{
			materialName = "default.png";
			finalTexturePath = "Textures\\" + materialName;
		}

		//materialName = "default.png";
		//finalTexturePath = "Textures\\" + materialName;

		//materialName = "arm_dif.png";
		//finalTexturePath = "Models\\nanosuit\\" + materialName;

		// Create texture
		std::string diffuseID = modelName + "_" + materialName;
		subset.m_mat.diffuseID = texService.addSRV(finalTexturePath, diffuseID);
		
		subsets.push_back(subset);
	}

	// Create texture batched subsets
	std::map<std::string, std::vector<Mesh::Subset>> matToMesh;

	for (const auto& subset : subsets)
	{
		// found
		const auto& el = matToMesh.find(subset.m_mat.diffuseID);
		if (el != matToMesh.end())
		{
			el->second.push_back(subset);
		}
		else
		{
			std::vector<Mesh::Subset> initSubset = { subset };
			matToMesh.insert({ subset.m_mat.diffuseID, initSubset });
		}
	}

	return std::make_shared<Mesh>(vboID, iboID, matToMesh);
}

