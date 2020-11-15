#include "Mesh.h"

Mesh::Mesh(const std::string& vboID, const std::string& iboID, std::map<std::string, std::vector<Mesh::Subset>> textureBatchedSubsets) :
	m_vboID(vboID),
	m_iboID(iboID),
	m_shouldRender(true),
	m_textureBatchedSubsets(textureBatchedSubsets)
{

}

Mesh::~Mesh()
{
}

void Mesh::setWorldMatrix(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot, float scale)
{
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateScale(scale);

	/*
		"Angle of rotation around the x-axis, in radians. Angles are measured clockwise when looking at the rotation axis [toward] the origin."
		Left hand!
	*/

	// LH matrices - these two are the same
	//m_worldMatrix *= DirectX::XMMatrixRotationX(rot.x);
	//m_worldMatrix *= DirectX::XMMatrixRotationY(rot.y);
	//m_worldMatrix *= DirectX::XMMatrixRotationZ(rot.z);

	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);		// Same??

	//m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationX(rot.x);
	//m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(rot.y);
	//m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationZ(rot.z);

	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(pos);

}

void Mesh::setRenderMode(bool mode)
{
	m_shouldRender = mode;
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

const std::map<std::string, std::vector<Mesh::Subset>>& Mesh::getTextureBatchedSubsets()
{
	return m_textureBatchedSubsets;
}

bool Mesh::shouldRender()
{
	return m_shouldRender;
}


bool Mesh::Subset::Material::operator<(const Mesh::Subset::Material& rhs)
{
	if (diffuseID < rhs.diffuseID)
	{
		return true;
	}
	return false;
}

