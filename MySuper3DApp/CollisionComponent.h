#pragma once
#include "Component.h"
#include <vector>
#include "KatamariObject.h"

using namespace DirectX;

class CollisionComponent : public Component
{
public:

    Matrix World;
    BoundingSphere* sphereCollision;
    std::vector<BoundingSphere*> collisionComponents;
    Vector3 center;
    float radius;

    CollisionComponent(float radius, Vector3 center);
    
    void Initialize();
    void Update();
};
