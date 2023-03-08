#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() : Component()
{

}

CollisionComponent::~CollisionComponent()
{
	
}

void CollisionComponent::Initialize()
{

}

void CollisionComponent::Update()
{
	
}

void CollisionComponent::AddCubeCollision(float radius)
{
	DirectX::BoundingBox* BBBox = new DirectX::BoundingBox();
	BBBox->Center = { Vector3::Zero };
	BBBox->Extents = { radius, radius, radius };
}
void CollisionComponent::AddSphereCollision(float size)
{

}