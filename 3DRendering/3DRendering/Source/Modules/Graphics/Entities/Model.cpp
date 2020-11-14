#include "Model.h"

Model::Model(std::shared_ptr<Mesh> mesh) :
	m_mesh(mesh)
{
}

Model::~Model()
{
}

void Model::update(float dt)
{
	m_mesh->setWorldMatrix(m_pos, m_rot, m_scale);
}
