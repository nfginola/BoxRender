#pragma once
#include "GameEntity.h"
#include <DirectXTK/SimpleMath.h>

class Player : public GameEntity
{
private:
	std::shared_ptr<Camera> m_cam;
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Input::InputEngine> m_input;

	float m_speed;

	void checkKeyboardInput(float dt);
	void checkMouseInput(float dt);

	void updateCameraOrientation(std::pair<float, float> mouseDeltaXY, float dt);
	void move(float leftRight, float forwardBack, float upDown, float dt);

public:
	Player(std::shared_ptr<Camera> cam, std::shared_ptr<Mesh> mesh, std::shared_ptr<Input::InputEngine> input);
	~Player();

	void update(float dt) override;


	std::shared_ptr<Camera> getCamera();
	std::shared_ptr<Mesh> getMesh();
};

