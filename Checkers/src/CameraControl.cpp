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
		moveUp();

	if (Input::getKeyDown(KeyCode::s))
		moveDown();
}

void CameraControl::setLookAtTarget(Vector3 target)
{
	lookAtTarget = target;
}

void CameraControl::moveUp()
{
	Vector3 position = transform->getPosition();
	position[1] += (speed * dt);
	if (position[1] > 1)
		position[1] = 1;
	transform->setPosition(position);

	Vector3 lookAt;

	//lookAt[0] = lookAtTarget[0] - position[0];
	//lookAt[1] = lookAtTarget[1] - position[1];
	//lookAt[2] = lookAtTarget[2] - position[2];

	getGameObject()->getComponent<Camera>()->setLookAt(lookAt);
}

void CameraControl::moveDown()
{
	Vector3 position = transform->getPosition();
	position[1] -= (speed * dt);
	if (position[1] < -1)
		position[1] = -1;
	transform->setPosition(position);

	Vector3 lookAt;

	lookAt = lookAtTarget - position;

	getGameObject()->getComponent<Camera>()->setLookAt(lookAt);
}