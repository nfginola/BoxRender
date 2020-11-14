#include "Mesh.h"

Mesh::Mesh(const std::string& vboID, const std::string& iboID, std::vector<Subset> subsets) :
	m_vboID(vboID),
	m_iboID(iboID),
	m_subsets(subsets)
{

}

Mesh::~Mesh()
{
}

void Mesh::setWorldMatrix(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, float scale)
{
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateScale(scale);

	// Right handed matrices
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationX(-rot.x);
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(-rot.y);
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationZ(-rot.z);

	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(pos);

}

const DirectX::SimpleMath::Matrix& Mesh::getWorldMatrix()
{
	return m_worldMatrix;
}

const std::string& Mesh::getVBOID()
{
	return m_vboID;
}

const std::string& Mesh::getIBOID()
{
	return m_iboID;

}

const std::vector<Mesh::Subset>& Mesh::getSubsets()
{
	return m_subsets;
}
