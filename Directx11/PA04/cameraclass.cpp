////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	m_fixPositiony = y;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}


void CameraClass::UpdateCamera(float moveLeftRight, float moveBackForward, float pitchDelta, float yawDelta)
{
	// Yaw 및 Pitch 업데이트
	m_rotation.x += pitchDelta;
	m_rotation.y += yawDelta;

	// Pitch 제한
	if (m_rotation.x > 89.0f) m_rotation.x = 89.0f;
	if (m_rotation.x < -89.0f) m_rotation.x = -89.0f;

	// 카메라 회전 행렬 계산
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x * 0.0174532925f, m_rotation.y * 0.0174532925f, 0);

	// 전방 및 오른쪽 벡터 갱신
	XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	forward = XMVector3TransformCoord(forward, camRotationMatrix);
	right = XMVector3TransformCoord(right, camRotationMatrix);

	// 이동 벡터 계산
	m_position.y = m_fixPositiony;
	XMVECTOR position = XMLoadFloat3(&m_position);
	position += right * moveLeftRight + forward * moveBackForward;


	// 최종 위치 갱신
	XMStoreFloat3(&m_position, position);

	// 뷰 행렬 업데이트
	Render();
}
