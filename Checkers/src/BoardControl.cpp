#include "BoardControl.h"

BoardControl::BoardControl()
{
	rotateSpeed = 1.0f;
	//xRatio = 1;
	//zRatio = 0;
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

	/*
	if (Input::getKeyDown(KeyCode::w))
		rotateBackward();

	if (Input::getKeyDown(KeyCode::s))
		rotateForward();
		*/
}

void BoardControl::rotateLeft()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[1] -= (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation); 
	//mapRatioToY(eulerRotation[1]);
}

void BoardControl::rotateRight()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[1] += (rotateSpeed * dt);
	transform->setEulerRotation(eulerRotation);
	//mapRatioToY(eulerRotation[1]);
}

/*
void BoardControl::rotateForward()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	eulerRotation[0] += (rotateSpeed * xRatio *dt);
	eulerRotation[2] += (rotateSpeed * zRatio * dt);
	transform->setEulerRotation(eulerRotation);
}

void BoardControl::rotateBackward()
{
	Vector3 eulerRotation = transform->getEulerRotation();
	
	XZAngle -= rotateSpeed * dt;

	eulerRotation[0] = xRatio * XZAngle;
	eulerRotation[2] = zRatio * XZAngle;
	transform->setEulerRotation(eulerRotation);
}

void BoardControl::mapRatioToY(float yRot){
	xRatio = cosf(yRot);
	zRatio = sinf(yRot);
}
*/