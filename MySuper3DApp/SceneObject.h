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

    void CreateCube(float sideSize);
    void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);

    virtual Vector3 GetPosition() const override;
    
    Vector3 rotationAxis;
    Vector3 orbitAxis;
    float rotationSpeed;
    float orbitSpeed;
    Quaternion rotator;
    Quaternion orbitalRotation;
};
