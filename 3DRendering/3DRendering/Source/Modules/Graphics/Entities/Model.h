#pragma once

#include "GameEntity.h"

class Model : public GameEntity
{
private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<DirectX::BoundingOrientedBox> m_boundingBox;

	DirectX::SimpleMath::Vector3 m_boundingBoxOffsets;

public:
	Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<DirectX::BoundingOrientedBox> boundingBox);
	~Model();

	void update(float dt) override;

	void setScale(float scale);
	void setRotation(const DirectX::SimpleMath::Vector3& radRot);

	void setBoundingBoxOffsets(const DirectX::SimpleMath::Vector3& offset);
	std::shared_ptr<DirectX::BoundingOrientedBox> getBoundingBox();
	std::shared_ptr<Mesh> getMesh();

};

