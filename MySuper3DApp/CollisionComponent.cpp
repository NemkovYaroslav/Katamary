#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(float radius, Vector3 center) : Component()
{
	this->sphereCollision = nullptr;
	this->center = center;
	this->radius = radius;
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