#include "Camera.h"
#include "Game.h"
#include "DisplayWin32.h"
#include "CameraController.h"

Camera::Camera()
{
	position = Vector3(Vector3::Up * 5);
	target   = Vector3(Vector3::Zero);
	up       = Vector3(Vector3::Up);
	cameraController = nullptr;
}

void Camera::Update(float deltaTime)
{
	if (cameraController)
	{
		cameraController->Update(deltaTime);
	}

	view = Matrix::CreateLookAt(position, target, up);

	if (isPerspectiveProjection)
	{
		projection = Matrix::CreatePerspectiveFieldOfView(
			fovAngle,
			static_cast<float>(Game::GetInstance()->GetDisplay()->GetClientWidth()) / Game::GetInstance()->GetDisplay()->GetClientHeight(),
			0.1f,
			1000.0f);
	}
	else
	{
		projection = Matrix::CreateOrthographic(
			Game::GetInstance()->GetDisplay()->GetClientWidth() / 40,
			Game::GetInstance()->GetDisplay()->GetClientHeight() / 40,
			0.1f,
			1000);
	}
}

Matrix Camera::GetWorldViewProjectionMatrix(Matrix World)
{
	return World * view * projection;
}

CameraController* Camera::GetCameraController()
{
	return cameraController;
}
void Camera::SetCameraController(CameraController* cameraController)
{
	this->cameraController = cameraController;
}