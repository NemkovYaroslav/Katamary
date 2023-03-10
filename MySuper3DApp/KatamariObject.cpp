#include "KatamariObject.h"

#include "Game.h"
#include "InputDevice.h"
#include "Camera.h"
#include "CameraController.h"

KatamariObject::KatamariObject(GameObject* parent, float radius) : GameObject(parent)
{
	this->rotationAxis = Vector3::UnitY;
	this->rotationSpeed = 0;
	this->rotation = Quaternion::Identity;
	//this->collisionComponent = nullptr;
}

void KatamariObject::Initialize()
{
	//collisionComponent = new CollisionComponent();
	rotationAxis.Normalize();
	GameObject::Initialize();
}

void KatamariObject::Update(float deltaTime)
{
	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(Game::GetInstance()->GetCamera()->GetCameraController()->yaw, 0, 0);

	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
	{
		rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Backward, rotationMatrix), rotationSpeed * deltaTime);
		position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Left, rotationMatrix);
	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
	{
		rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Forward, rotationMatrix), rotationSpeed * deltaTime);
		position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Right, rotationMatrix);
	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
	{
		rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Left, rotationMatrix), rotationSpeed * deltaTime);
		position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Forward, rotationMatrix);
	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
	{
		rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Right, rotationMatrix), rotationSpeed * deltaTime);
		position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Backward, rotationMatrix);
	}
	SetRotation(rotation);
	renderComponent->World = GetWorld();

	//collisionComponent->radius = radius;
	//collisionComponent->center = position;

	//std::cout << (position == collisionComponent->center) << std::endl;

	GameObject::Update(deltaTime);
}

void KatamariObject::UpdateWorld()
{
	GameObject::UpdateWorld();
}

/*
Vector3 KatamariObject::GetPosition() const
{
	if (parent)
	{
		//return Vector3::Transform(GameObject::GetPosition(), Matrix::CreateTranslation(parent->GetPosition()));
	}
	return GameObject::GetPosition();
}
*/