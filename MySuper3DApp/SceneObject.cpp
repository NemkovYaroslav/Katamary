#include "SceneObject.h"
#include "RenderComponent.h"

SceneObject::SceneObject(SceneObject* parent) : GameObject(parent)
{

}

void SceneObject::Initialize()
{
	GameObject::Initialize();
}

void SceneObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void SceneObject::UpdateWorld()
{

}