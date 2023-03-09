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

	void CreateCube(float radius);
	void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);

	virtual Matrix GetWorld() const;
	virtual Quaternion GetRotation() const;
	virtual Vector3 GetPosition() const;
	virtual void SetWorld(const Vector3& position, const Quaternion& rotation);
	virtual void SetRotation(const Quaternion& rotation);
	virtual void SetPosition(const Vector3& position);
};