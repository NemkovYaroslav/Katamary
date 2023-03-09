#pragma once
#include "GameObject.h"

class RenderComponent;
class CollisionComponent;

class KatamariObject : public GameObject
{
public:

    KatamariObject(KatamariObject* parent = nullptr);

    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
    virtual void UpdateWorld() override;

    virtual Vector3 GetPosition() const override;

    Vector3 rotationAxis;
    float rotationSpeed;
    Quaternion rotator;

    bool isKatamari;
};
