#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <utility>

#include <DirectXTK/SimpleMath.h>

class Camera
{
private:
	DirectX::SimpleMath::Vector4 m_camForward, m_camRight, m_camUp, m_upDir;
	DirectX::SimpleMath::Vector3 m_pos;

	DirectX::SimpleMath::Matrix m_viewMatrix, m_projectionMatrix;

	float m_fovAngleRad, m_aspectRatio, m_nearZ, m_farZ;
	float m_camPitch, m_camYaw;

public:
	Camera(float fovAngleDeg, float aspectRatio, float nearZ, float farZ);
	~Camera();

	void updateOrientation(std::pair<float, float> mouseDeltaXY, float dt);
	void setPosition(DirectX::SimpleMath::Vector3 newPos);

	DirectX::SimpleMath::Vector4 getForwardVector();
	DirectX::SimpleMath::Vector4 getRightVector();
	DirectX::SimpleMath::Vector4 getUpVector();
	DirectX::SimpleMath::Vector3 getPosition();
	DirectX::SimpleMath::Matrix getViewMatrix();
	DirectX::SimpleMath::Matrix getProjectionMatrix();
};

