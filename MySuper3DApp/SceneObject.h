#pragma once
#include "GameObject.h"

class SceneObject : public GameObject
{
public:

    SceneObject(GameObject* parent = nullptr, float radius = 1.0f);

    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
    virtual void UpdateWorld() override;

    //virtual Vector3 GetPosition() const override;
};
