#include "BoardControl.h"

BoardControl::BoardControl()
{
	rotateSpeed = 1.0f;
}

void BoardControl::Start()
{
	transform = getGameObject()->getTransform();
}

void BoardControl::Update()
{
	dt = GameTime::GetDeltaTime();

	if (Input::getKeyDown(KeyCode::a))
		rotateLeft();

	if (Input::getKeyDown(KeyCode::d))
		rotateRight();

	if (Input::getKeyDown(KeyCode::w))
		rotateBackward();

	if (Input::getKeyDown(KeyCode::s))
		rotateForward();
}

void BoardControl::rotateLeft()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[1] -= (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation);
}

void BoardControl::rotateRight()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[1] += (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation);
}

void BoardControl::rotateForward()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[0] += (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation);
}

void BoardControl::rotateBackward()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[0] -= (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation);
}