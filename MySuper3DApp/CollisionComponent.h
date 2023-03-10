#pragma once
#include "Component.h"

#include <vector>

using namespace DirectX::SimpleMath;

class CollisionComponent : public Component
{
public:

    Matrix World;

    Vector3 center;
    float radius;
    DirectX::BoundingSphere* sphereCollision;
    std::vector<DirectX::BoundingSphere*> collisionComponents;

    CollisionComponent();
    
    void Initialize();
    void Update();
};
