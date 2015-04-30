#pragma once

#include "BrickwareCore\Component.hpp"
#include "BrickwareCore\Input.hpp"
#include "BrickwareCore\GameObject.hpp"
#include "BrickwareCore\GameTime.hpp"
#include "BrickwareCore\Camera.hpp"

#include "BrickwareMath\Vector3.hpp"
#include "BrickwareMath\Quaternion.hpp"

using namespace Brickware;
using namespace Core;
using namespace Math;

class CameraControl : public Component
{
public:
	CameraControl();

	virtual void Start() override;
	virtual void Update() override;

private:
	Transform* transform;
	float dt;
	float speed;

	float radianIncrement = 2;

	float pitch = 0;
	float yaw = 0;
};