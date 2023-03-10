#include "SceneObject.h"

SceneObject::SceneObject(GameObject* parent, float radius) : GameObject(parent)
{

}

void SceneObject::Initialize()
{
	GameObject::Initialize();
}

void SceneObject::Update(float deltaTime)
{
	SetRotation(Quaternion::Identity);
	renderComponent->World = GetWorld();
	GameObject::Update(deltaTime);
}

void SceneObject::UpdateWorld()
{
	GameObject::UpdateWorld();
}

/*
Vector3 SceneObject::GetPosition() const
{
	if (parent)
	{
		return Vector3::Transform(GameObject::GetPosition(), Matrix::CreateTranslation(parent->GetPosition()));
	}
	return GameObject::GetPosition();
}
*/