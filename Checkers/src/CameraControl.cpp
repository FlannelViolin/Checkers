#include "CameraControl.h"

CameraControl::CameraControl()
{
	speed = 1.0f;
}

void CameraControl::Start()
{
	transform = getGameObject()->getTransform();
}

void CameraControl::Update()
{
	dt = GameTime::GetDeltaTime();

	if (Input::getKeyDown(KeyCode::w))
		pitch += radianIncrement * dt;

	if (Input::getKeyDown(KeyCode::s))
		pitch -= radianIncrement * dt;

	if (Input::getKeyDown(KeyCode::d))
		yaw += radianIncrement * dt;

	if (Input::getKeyDown(KeyCode::a))
		yaw -= radianIncrement * dt;

	Vector3 pos = transform->getPosition();
	Vector3 rot = transform->getEulerRotation();

	float x = 3 * sinf(yaw) * cosf(pitch);
	float y = 3 * sinf(pitch);
	float z = 3 * cosf(yaw) * cosf(pitch);

	pos[0] = x;
	pos[1] = y;
	pos[2] = z;

	rot[0] = -pitch;
	rot[1] = yaw;

	transform->setPosition(pos);
	transform->setEulerRotation(rot);
}