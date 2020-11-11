#include "AssimpModelLoader.h"

AssimpModelLoader::AssimpModelLoader() :
	m_meshVertexCount(0),
	m_meshIndexCount(0)
{

}

AssimpModelLoader::~AssimpModelLoader()
{
}

IModelLoader::EngineStaticMeshData AssimpModelLoader::LoadStaticModel(std::string filePath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		filePath, 
		aiProcess_Triangulate | 
		aiProcess_ConvertToLeftHanded |
		aiProcess_GenNormals
	);

	if (scene == nullptr)
	{
		OutputDebugStringW(L"Assimp: File not found!");
		assert(false);
	}

	unsigned int totalVertexCount = 0;
	unsigned int totalSubsetCount = 0;
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		totalVertexCount += scene->mMeshes[i]->mNumVertices;
		++totalSubsetCount;
	}
	m_vertices.reserve(totalVertexCount);
	m_indices.reserve(totalVertexCount);
	m_subsets.reserve(totalSubsetCount);

	ProcessNode(scene->mRootNode, scene);

	EngineStaticMeshData data;
	data.m_indices = m_indices;
	data.m_vertices = m_vertices;
	data.m_subsetsInfo = m_subsets;

	m_indices.clear();
	m_vertices.clear();
	m_subsets.clear();
	return data;
}

void AssimpModelLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
	// For each mesh in the node, process it!
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}

}

// Subset of Mesh
void AssimpModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vert = { };
		vert.m_position.x = mesh->mVertices[i].x;
		vert.m_position.y = mesh->mVertices[i].y;
		vert.m_position.z = mesh->mVertices[i].z;

		vert.m_normal.x = mesh->mNormals[i].x;
		vert.m_normal.y = mesh->mNormals[i].y;
		vert.m_normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			vert.m_texCoord.u = mesh->mTextureCoords[0][i].x;
			vert.m_texCoord.v = mesh->mTextureCoords[0][i].y;
		}

		m_vertices.push_back(vert);
	}

	unsigned int indicesThisMesh = 0;
	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; ++j)
		{
			m_indices.push_back(face.mIndices[j]);
			++indicesThisMesh;
		}

	}

	// Get material
	auto mtl = scene->mMaterials[mesh->mMaterialIndex];
	aiString diffPath, norPath;
	mtl->GetTexture(aiTextureType_DIFFUSE, 0, &diffPath);
	mtl->GetTexture(aiTextureType_HEIGHT, 0, &norPath);

	// Subset data
	EngineStaticMeshSubset subsetData = { };
	subsetData.m_diffuseFilePath = diffPath.C_Str();
	subsetData.m_normalFilePath = norPath.C_Str();

	subsetData.m_vertexCount = mesh->mNumVertices;
	subsetData.m_vertexStart = m_meshVertexCount;
	m_meshVertexCount += mesh->mNumVertices;

	subsetData.m_indexCount = indicesThisMesh;
	subsetData.m_indexStart = m_meshIndexCount;
	m_meshIndexCount += indicesThisMesh;
	
	m_subsets.push_back(subsetData);
}

