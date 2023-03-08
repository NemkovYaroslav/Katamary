#pragma once
#include "includes.h"
#include "InputDevice.h"

class Camera;

class CameraController
{
protected:

	float cameraRotationSpeed = 0.005f;
	float yaw = 0;
	float pitch = 0;
	bool wasCameraControllerKeyDown = false;

public:

	CameraController();
	virtual void Update(float deltaTime) = 0;

	virtual void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) = 0;
};
