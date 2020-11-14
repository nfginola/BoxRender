#pragma once
#include <DirectXTK/SimpleMath.h>
#include <DirectXCollision.h>
#include <memory>
#include "../Components/Camera.h"
#include "../Engine/D3D11/Mesh/Mesh.h"
#include "../Engine/ModelLoader/LoaderUtility.h"
#include "../../Input/InputEngine.h"


class GameEntity
{
protected:
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_rot;
	float m_scale;

public:
	GameEntity();
	virtual ~GameEntity();

	virtual void update(float dt) = 0;

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	void setRotation(DirectX::SimpleMath::Vector3 rot);
	void setScale(float scale);

	DirectX::SimpleMath::Vector3 getPosition();
	DirectX::SimpleMath::Vector3 getRotation();
	float getScale();

};

