#pragma once
#include "CameraController.h"

using namespace DirectX::SimpleMath;

class TPSCameraController : public CameraController
{
public:

    float armLength = 5.0f;
    GameObject* curObject = Game::GetInstance()->GameObjects.at(0);

    TPSCameraController();
    virtual void Update(float deltaTime) override;

    virtual void MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) override;
};
