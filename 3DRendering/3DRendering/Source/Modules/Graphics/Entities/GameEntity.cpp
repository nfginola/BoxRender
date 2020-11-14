#include "GameEntity.h"

using namespace DirectX::SimpleMath;

GameEntity::GameEntity() :
	m_pos(Vector3(0.f, 0.f, 0.f)),
	m_rot(Vector3(0.f, 0.f, 0.f)),
	m_scale(1.f)
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::setPosition(DirectX::SimpleMath::Vector3 pos)
{
	m_pos = pos;
}

// 
void GameEntity::setRotation(DirectX::SimpleMath::Vector3 rot)
{
	// LH rotation!
	m_rot = rot;
}

void GameEntity::setScale(float scale)
{
	m_scale = scale;
}

DirectX::SimpleMath::Vector3 GameEntity::getPosition()
{
	return m_pos;
}

DirectX::SimpleMath::Vector3 GameEntity::getRotation()
{
	return m_rot;
}

float GameEntity::getScale()
{
	return m_scale;
}
