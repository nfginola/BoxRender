#pragma once
#include "../DeviceManager/D3D11DeviceManager.h"
#include <string>
#include <vector>
#include <DirectXTK/SimpleMath.h>

class Mesh
{
public:
	struct Subset
	{
		unsigned int m_indexCount;
		unsigned int m_indexStart;		// Where in the IB should we start reading from?
		unsigned int m_vertexStart;		// Where in the VB should we start reading from?

		std::string diffuseID;
	};

	struct Vertex
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 nor;
		DirectX::SimpleMath::Vector2 uv;

	};
private:
	std::string m_vboID, m_iboID;
	std::vector<Subset> m_subsets;

	DirectX::SimpleMath::Matrix m_worldMatrix;

public:
	Mesh(const std::string& vboID, const std::string& iboID, std::vector<Subset> subsets);
	~Mesh();

	void setWorldMatrix(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, float scale);

	const DirectX::SimpleMath::Matrix& getWorldMatrix();
	const std::string& getVBOID();
	const std::string& getIBOID();
	const std::vector<Subset>& getSubsets();


};

