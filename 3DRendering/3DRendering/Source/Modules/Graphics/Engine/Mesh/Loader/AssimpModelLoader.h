#pragma once
#include "IModelLoader.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class AssimpModelLoader : public IModelLoader
{
public:
	AssimpModelLoader();
	~AssimpModelLoader();

	EngineStaticMeshData LoadStaticModel(std::string filePath) override;

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<EngineStaticMeshSubset> m_subsets;

	// Keep track of submesh offset in m_vertices and m_indices respectively
	unsigned int m_meshVertexCount;
	unsigned int m_meshIndexCount;

	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

