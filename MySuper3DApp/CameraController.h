#pragma once
#include "includes.h"
#include "InputDevice.h"

class Camera;

using namespace DirectX::SimpleMath;

class CameraController
{
protected:

	float cameraRotationSpeed = 0.005f;
	bool wasCameraControllerKeyDown = false;

public:

	float yaw = 0;
	float pitch = 0;

	Matrix rotationMatrix;

	CameraController();
	virtual void Update(float deltaTime) = 0;

	virtual void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) = 0;
};
