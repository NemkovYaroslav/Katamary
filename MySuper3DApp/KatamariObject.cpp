#include "KatamariObject.h"
#include "RenderComponent.h"
#include "Game.h"
#include "InputDevice.h"

KatamariObject::KatamariObject(KatamariObject* parent) : GameObject(parent)
{
	this->rotationAxis = Vector3::UnitY;
	this->rotationSpeed = 0;
	this->rotator = Quaternion::Identity;
	this->isKatamari = false;
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
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::UnitZ, rotationSpeed * deltaTime);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
		{
			rotator *= Quaternion::CreateFromAxisAngle(-Vector3::UnitZ, rotationSpeed * deltaTime);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
		{
			rotator *= Quaternion::CreateFromAxisAngle(-Vector3::UnitX, rotationSpeed * deltaTime);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
		{
			rotator *= Quaternion::CreateFromAxisAngle(Vector3::UnitX, rotationSpeed * deltaTime);
		}
	}
	std::cout << " X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
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