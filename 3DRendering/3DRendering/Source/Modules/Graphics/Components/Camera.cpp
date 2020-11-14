#include "Camera.h"

using namespace DirectX::SimpleMath;

Camera::Camera(float fovAngleDeg, float aspectRatio, float nearZ = 0.1f, float farZ = 150.f) :
	m_pos(DirectX::SimpleMath::Vector4(0.f, 0.f, 0.f, 1.f)),
	m_aspectRatio(aspectRatio),
	m_nearZ(nearZ),
	m_farZ(farZ),
	m_camForward(DirectX::SimpleMath::Vector4(0.f, 0.f, 1.f, 0.f)),
	m_camUp(DirectX::SimpleMath::Vector4(0.f, 1.f, 0.f, 0.f)),
	m_camRight(DirectX::SimpleMath::Vector4(1.f, 0.f, 0.f, 0.f)),
	m_upDir(DirectX::SimpleMath::Vector4(0.f, 1.f, 0.f, 0.f)),
	m_camYaw(0),
	m_camPitch(0)
{
	m_fovAngleRad = (M_PI / 180.f) * (fovAngleDeg);
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(m_fovAngleRad, aspectRatio, nearZ, farZ);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(Vector4(0.f, 0.f, 0.f, 1.f), Vector4(0.f, 0.f, 1.f, 1.f), Vector4(0.f, 1.f, 0.f, 0.f));
}

Camera::~Camera()
{
}

void Camera::updateOrientation(std::pair<float, float> mouseDeltaXY, float dt)
{
	// Update the pitch and yaw values for camera
	// Mouse still depends on FPS!
	// If we use deltaTime then Raw Input will be very noticable! (Jagged movement)
	float deltaYaw = mouseDeltaXY.first * 0.003f;
	float deltaPitch = mouseDeltaXY.second * 0.003f;

	m_camPitch += deltaPitch;
	m_camYaw += deltaYaw;

	// Set camera rotation limit (up/down)
	if (m_camPitch > 89.f * (M_PI / 180.f))
	{
		m_camPitch = 89.f * (M_PI / 180.f);
	}
	else if (m_camPitch < -89.f * (M_PI / 180.f))
	{
		m_camPitch = -89.f * (M_PI / 180.f);
	}

	Matrix camRotationMatrix = Matrix::CreateFromYawPitchRoll(m_camYaw, m_camPitch, 0.f);

	// New orientation
	m_camRight = Vector4::Transform(Vector4(1.0f, 0.0f, 0.0f, 0.0f), camRotationMatrix);
	//m_camUp = Vector4(0.f, 1.f, 0.f, 0.f);
	m_camForward = Vector4::Transform(Vector4(0.0f, 0.0f, 1.0f, 0.0f), camRotationMatrix);

	Vector4 camTarget = m_pos + m_camForward;

	m_viewMatrix = DirectX::XMMatrixLookAtLH(m_pos, camTarget, m_camUp);
}

void Camera::setPosition(DirectX::SimpleMath::Vector3 newPos)
{
	m_pos = newPos;
	m_viewMatrix = DirectX::XMMatrixLookAtLH(m_pos, m_pos + m_camForward, m_camUp);
}

DirectX::SimpleMath::Vector4 Camera::getForwardVector()
{
	return m_camForward;
}

DirectX::SimpleMath::Vector4 Camera::getRightVector()
{
	return m_camRight;
}

DirectX::SimpleMath::Vector4 Camera::getUpVector()
{
	return m_camUp;
}

DirectX::SimpleMath::Vector3 Camera::getPosition()
{
	return m_pos;
}

DirectX::SimpleMath::Matrix Camera::getViewMatrix()
{
	return m_viewMatrix;
}

DirectX::SimpleMath::Matrix Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}
