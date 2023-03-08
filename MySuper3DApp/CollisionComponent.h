#pragma once
#include "Component.h"
#include <vector>

using namespace DirectX::SimpleMath;

class CollisionComponent : public Component
{
public:

    Matrix World;

    CollisionComponent();
    ~CollisionComponent();
    
    void Initialize();
    void Update();

    void AddCubeCollision(float radius);
    void AddSphereCollision(float radius);
};
