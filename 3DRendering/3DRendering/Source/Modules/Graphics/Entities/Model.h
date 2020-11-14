#pragma once

#include "GameEntity.h"

class Model : public GameEntity
{
private:
	std::shared_ptr<Mesh> m_mesh;
	DirectX::BoundingBox m_aabb;

public:
	Model(std::shared_ptr<Mesh> mesh, DirectX::BoundingBox aabb);
	~Model();

	void update(float dt) override;

	void setScale(float scale);

	const DirectX::BoundingBox& getAABB();
	std::shared_ptr<Mesh> getMesh();

};

