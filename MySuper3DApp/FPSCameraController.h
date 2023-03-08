#pragma once
#include "CameraController.h"

class FPSCameraController : public CameraController
{
public:

    float cameraSpeed = 5.0f;
    float cameraFOVSpeed = 0.001f;

    FPSCameraController();
    virtual void Update(float deltaTime) override;

    virtual void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) override;
};
