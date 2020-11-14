#pragma once
#include "../DeviceManager/D3D11DeviceManager.h"
#include <string>
#include <vector>
#include <map>
#include <DirectXTK/SimpleMath.h>

class Mesh
{
public:
	struct Subset
	{
		struct Material
		{
			std::string diffuseID;

			bool operator<(const Material& rhs);

		};


		unsigned int m_indexCount;
		unsigned int m_indexStart;		// Where in the IB should we start reading from?
		unsigned int m_vertexStart;		// Where in the VB should we start reading from?

		Material m_mat;
	};

	struct Vertex
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 nor;
		DirectX::SimpleMath::Vector2 uv;

	};
private:
	std::string m_vboID, m_iboID;

	std::map<std::string, std::vector<Mesh::Subset>> m_textureBatchedSubsets;

	DirectX::SimpleMath::Matrix m_worldMatrix;

	bool m_shouldRender;

public:
	Mesh(const std::string& vboID, const std::string& iboID, std::map<std::string, std::vector<Mesh::Subset>> textureBatchedSubsets);
	~Mesh();

	void setWorldMatrix(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, float scale);
	void setRenderMode(bool mode);

	const DirectX::SimpleMath::Matrix& getWorldMatrix();
	const std::string& getVBOID();
	const std::string& getIBOID();
	const std::map<std::string, std::vector<Mesh::Subset>>& getTextureBatchedSubsets();
	bool shouldRender();

};

