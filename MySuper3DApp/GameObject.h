#pragma once
#include "includes.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

class Component;

using namespace DirectX::SimpleMath;

class GameObject
{
protected:

	Quaternion rotation;
	Vector3 position;

	Matrix world;
	GameObject* parent = nullptr;

	RenderComponent* renderComponent;
	CollisionComponent* collisionComponent;
	std::vector<Component*> components;

public:

	GameObject(GameObject* parent = nullptr);
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Initialize();
	virtual void UpdateWorld();

	virtual Matrix GetWorld() const;
	virtual Quaternion GetRotation() const;
	virtual Vector3 GetPosition() const;
	virtual void SetWorld(const Vector3& newPosition, const Quaternion& newRotation);
	virtual void SetRotation(const Quaternion& newRotation);
	virtual void SetPosition(const Vector3& newPosition);
};