#pragma once
#include "GameObject.h"

class RenderComponent;

class SceneObject : public GameObject
{
public:

    SceneObject(SceneObject* parent = nullptr);

    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
    virtual void UpdateWorld() override;
};
