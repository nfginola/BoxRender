#include "Model.h"

Model::Model(std::shared_ptr<Mesh> mesh, DirectX::BoundingBox aabb) :
	m_mesh(mesh),
	m_aabb(aabb)
{
}

Model::~Model()
{
}

void Model::update(float dt)
{

	m_aabb.Center = m_pos;
	m_mesh->setWorldMatrix(m_pos, m_rot, m_scale);
}

void Model::setScale(float scale)
{
	GameEntity::setScale(scale);
	m_aabb.Extents.x *= m_scale;
	m_aabb.Extents.y *= m_scale;
	m_aabb.Extents.z *= m_scale;
}

const DirectX::BoundingBox& Model::getAABB()
{
	return m_aabb;
}

std::shared_ptr<Mesh> Model::getMesh()
{
	return m_mesh;
}
