#pragma once

#include "GameEntity.h"

class Model : public GameEntity
{
private:
	std::shared_ptr<Mesh> m_mesh;

public:
	Model(std::shared_ptr<Mesh> mesh);
	~Model();

	void update(float dt) override;
};

