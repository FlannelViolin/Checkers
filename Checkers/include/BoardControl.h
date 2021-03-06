#pragma once

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Input.hpp"
#include "BrickwareCore\GameObject.hpp"
#include "BrickwareCore\GameTime.hpp"

#include "BrickwareMath\Vector3.hpp"
#include "BrickwareMath\Quaternion.hpp"

using namespace Brickware;
using namespace Core;
using namespace Math;

class BoardControl : public Component
{
public:
	BoardControl();

	virtual void Start() override;
	virtual void Update() override;

private:

	void rotateLeft();
	void rotateRight();
	/*
	void rotateForward();
	void rotateBackward();
	void mapRatioToY(float yRot);
	*/


	Transform* transform;
	float dt;
	float rotateSpeed;

	/*
	float XZAngle;

	float xRatio;
	float zRatio;
	*/
};