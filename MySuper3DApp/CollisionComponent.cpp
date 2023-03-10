#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() : Component()
{
	this->sphereCollision = nullptr;
	this->center = Vector3::Zero;
	this->radius = 0.0f;
}

void CollisionComponent::Initialize()
{
	this->sphereCollision = new DirectX::BoundingSphere();
	sphereCollision->Center = center;
	sphereCollision->Radius = radius;
	collisionComponents.push_back(sphereCollision);
}

void CollisionComponent::Update()
{
	for (const auto& collision : collisionComponents)
	{
		if ((sphereCollision->Intersects(*collision)) )
		{
			std::cout << (sphereCollision == collision) << std::endl;
		}
	}
}