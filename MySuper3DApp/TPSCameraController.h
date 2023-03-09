#pragma once
#include "CameraController.h"

using namespace DirectX::SimpleMath;

class TPSCameraController : public CameraController
{
public:

    float armLength = 5.0f;

    TPSCameraController();
    virtual void Update(float deltaTime) override;

    virtual void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) override;
};
