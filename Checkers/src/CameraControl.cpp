#include "CameraControl.h"

CameraControl::CameraControl(bool P)
{
	speed = 1.0f;
	paused = P;
	grace = true;
	UI->getTransform()->setScale(Vector3(0.75, 0.75, 0.75));
}

void CameraControl::Start()
{
	transform = getGameObject()->getTransform();
}

void CameraControl::Update()
{
	dt = GameTime::GetDeltaTime();
	if (!paused){
		if (Input::getKeyDown(KeyCode::w))
			pitch += radianIncrement * dt;

		if (Input::getKeyDown(KeyCode::s))
			pitch -= radianIncrement * dt;

		if (Input::getKeyDown(KeyCode::d))
			yaw += radianIncrement * dt;

		if (Input::getKeyDown(KeyCode::a))
			yaw -= radianIncrement * dt;


		if (Input::getKeyDown(KeyCode::space)){
			if (grace){
				paused = true;
				UI->getTransform()->setScale(Vector3(0.75, 0.75, 0.75));
				grace = false;
			}
		}
		if (Input::getKeyUp(KeyCode::space)){
			grace = true;
		}
	}
	else {
		yaw -= radianIncrement/5 * dt;
		pitch = 0;
		if (Input::getKeyDown(KeyCode::space)){
			if (grace){
				grace = false;
				paused = false;
				UI->getTransform()->setScale(Vector3(0, 0, 0));
				
			}
		}
		if (Input::getKeyUp(KeyCode::space)){
			grace = true; 
		}
	}

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
	
	UI->getTransform()->setEulerRotation(rot);

}