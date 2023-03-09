#include "KatamariObject.h"
#include "Game.h"
#include "InputDevice.h"
#include "Camera.h"
#include "CameraController.h"

KatamariObject::KatamariObject(KatamariObject* parent, float katamariRadius) : GameObject(parent)
{
	this->rotationAxis = Vector3::UnitY;
	this->rotationSpeed = 0;
	this->rotator = Quaternion::Identity;
	this->isKatamari = false;
	this->radius = 0;
	this->collisionComponent = nullptr;
	this->katamariRadius = katamariRadius;
}

void KatamariObject::Initialize()
{
	rotationAxis.Normalize();
	GameObject::Initialize();
}

void KatamariObject::Update(float deltaTime)
{
	if (isKatamari)
	{
		Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(Game::GetInstance()->GetCamera()->GetCameraController()->yaw, 0, 0);

		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Backward, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Left, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Forward, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Right, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Left, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Forward, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Right, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Backward, rotationMatrix);
		}
	}
	//std::cout << " X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
	SetRotation(rotator);
	renderComponent->World = GetWorld();
	GameObject::Update(deltaTime);
}

void KatamariObject::UpdateWorld()
{
	world = Matrix::CreateFromQuaternion(GameObject::GetRotation()) * Matrix::CreateTranslation(GameObject::GetPosition());
	if (parent)
	{
		world *= parent->GetWorld();
	}
}

Vector3 KatamariObject::GetPosition() const
{
	if (parent)
	{
		return Vector3::Transform(GameObject::GetPosition(), Matrix::CreateTranslation(parent->GetPosition()));
	}
	return GameObject::GetPosition();
}

void KatamariObject::CreateCube(float radius)
{
	renderComponent = new RenderComponent("../Shaders/MyVeryFirstShader.hlsl", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent->AddCube(radius);
	components.push_back(renderComponent);
}
void KatamariObject::CreateSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
{
	renderComponent = new RenderComponent("../Shaders/MyVeryFirstShader.hlsl", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent->AddSphere(radius, sliceCount, stackCount, color);
	components.push_back(renderComponent);
	if (isKatamari)
	{
		collisionComponent = new CollisionComponent(radius, position);
		components.push_back(collisionComponent);
	}
	else
	{
		collisionComponent = new CollisionComponent(radius + katamariRadius, position);
		components.push_back(collisionComponent);
	}
}