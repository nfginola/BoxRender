#include "Model.h"

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<DirectX::BoundingOrientedBox> aabb) :
	m_mesh(mesh),
	m_boundingBox(aabb)
{
}

Model::~Model()
{
}

void Model::update(float dt)
{
	//m_boundingBox->Center = m_pos + m_boundingBoxOffsets;
	m_boundingBox->Center = m_pos + m_boundingBoxOffsetsRotated;	// When mesh rotated, make sure to offset center with rotation taken into account!
	m_mesh->setWorldMatrix(m_pos, m_rot, m_scale);
}

void Model::setScale(float scale)
{
	GameEntity::setScale(scale);
	m_boundingBox->Extents.x *= m_scale;
	m_boundingBox->Extents.y *= m_scale;
	m_boundingBox->Extents.z *= m_scale;
}

void Model::setRotation(const DirectX::SimpleMath::Vector3& radRot)
{
	GameEntity::setRotation(radRot);
	m_boundingBox->Orientation = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(radRot.y, radRot.x, radRot.z));

	// We make sure to get the composants of the offset in the right space (mesh rotated space)
	m_boundingBoxOffsetsRotated = DirectX::SimpleMath::Vector3::Transform(m_boundingBoxOffsets, DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(radRot.y, radRot.x, radRot.z));

}

void Model::setBoundingBoxOffsets(const DirectX::SimpleMath::Vector3& offset)
{
	m_boundingBoxOffsets = offset;
	m_boundingBoxOffsetsRotated = m_boundingBoxOffsets;	// For initial --> Use this function BEFORE rotation!
}

std::shared_ptr<DirectX::BoundingOrientedBox> Model::getBoundingBox()
{
	return m_boundingBox;
}

std::shared_ptr<Mesh> Model::getMesh()
{
	return m_mesh;
}
