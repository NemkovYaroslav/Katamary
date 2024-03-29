#include "GameObject.h"

GameObject::GameObject(GameObject* parent)
{
	this->parent = parent;
	this->renderComponent = nullptr;
	//this->collisionComponent = nullptr;
	this->radius = 0.0f;
}
GameObject::~GameObject()
{
	for (const auto& component : components)
	{
		delete component;
	}
	components.clear();
}

void GameObject::Initialize()
{
	for (const auto& component : components)
	{
		component->Initialize();
	}
}

void GameObject::Update(float deltaTime)
{
	for (const auto& component : components)
	{
		component->Update();
	}
}

void GameObject::UpdateWorld()
{
	world = Matrix::CreateFromQuaternion(GameObject::GetRotation()) * Matrix::CreateTranslation(GameObject::GetPosition());
	if (parent)
	{
		world *= parent->GetWorld();
	}
}

void GameObject::CreateSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
{
	renderComponent = new RenderComponent("../Shaders/MyVeryFirstShader.hlsl", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent->AddSphere(radius, sliceCount, stackCount, color);
	components.push_back(renderComponent);
}

Matrix GameObject::GetWorld() const        { return world;    }
Quaternion GameObject::GetRotation() const { return rotation; }
Vector3 GameObject::GetPosition() const    { return position; }
void GameObject::SetWorld(const Vector3& position, const Quaternion& potation) { this->rotation = rotation; this->position = position; UpdateWorld(); }
void GameObject::SetRotation(const Quaternion& rotation)                       { this->rotation = rotation;                            UpdateWorld(); }
void GameObject::SetPosition(const Vector3& position)                          { this->position = position;                            UpdateWorld(); }