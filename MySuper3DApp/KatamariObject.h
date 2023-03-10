#pragma once
#include "GameObject.h"

class KatamariObject : public GameObject
{
public:

    KatamariObject(GameObject* parent = nullptr, float radius = 1.0f);

    Vector3 rotationAxis;
    float rotationSpeed;
    Quaternion rotation;

    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
    virtual void UpdateWorld() override;

    //virtual Vector3 GetPosition() const override;
};
