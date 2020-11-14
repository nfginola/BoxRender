#include "Player.h"

using namespace DirectX::SimpleMath;

void Player::checkKeyboardInput(float dt)
{
	const std::shared_ptr<Input::IKeyboardInput>& kb = m_input->getKeyboard();
	float moveLeftRight = 0.f;
	float moveForwardBack = 0.f; 
	float moveUpDown = 0.f;

	if (kb->isKeyDown("A"))
	{
		moveLeftRight = -1.f;
	}
	if (kb->isKeyDown("D"))
	{
		moveLeftRight = 1.f;
	}
	if (kb->isKeyDown("W"))
	{
		moveForwardBack = 1.f;
	}
	if (kb->isKeyDown("S"))
	{
		moveForwardBack = -1.f;
	}
	if (kb->isKeyDown("SPACE"))
	{
		moveUpDown = 1.f;
	}
	if (kb->isKeyDown("Q"))
	{
		moveUpDown = -1.f;
	}
	
	move(moveLeftRight, moveForwardBack, moveUpDown, dt);

}

void Player::checkMouseInput(float dt)
{
	updateCameraOrientation(std::pair<float, float>(m_input->getMouse()->getDeltaX(), m_input->getMouse()->getDeltaY()), dt);
}

Player::Player(std::shared_ptr<Camera> cam, std::shared_ptr<Mesh> mesh, std::shared_ptr<Input::InputEngine> input) :
	m_cam(cam),
	m_mesh(mesh),
	m_input(input),
	m_speed(10.f)
{

}

Player::~Player()
{
}

void Player::update(float dt)
{
	checkKeyboardInput(dt);
	checkMouseInput(dt);
}

void Player::updateCameraOrientation(std::pair<float, float> mouseDeltaXY, float dt)
{
	m_cam->updateOrientation(mouseDeltaXY, dt);
}


void Player::move(float leftRight, float forwardBack, float upDown, float dt)
{
	// Make sure to move with the correct orientation and correct speed (diagonal fix)
	Vector4 moveDirection = leftRight * m_cam->getRightVector() + forwardBack * m_cam->getForwardVector() + upDown * m_cam->getUpVector();
	moveDirection.Normalize();

	m_cam->setPosition(m_cam->getPosition() + moveDirection * m_speed * dt);
}

std::shared_ptr<Camera> Player::getCamera()
{
	return m_cam;
}

std::shared_ptr<Mesh> Player::getMesh()
{
	return m_mesh;
}
