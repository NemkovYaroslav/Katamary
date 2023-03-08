#include "FPSCameraController.h"

#include "Game.h"
#include "Camera.h"

FPSCameraController::FPSCameraController() : CameraController()
{
	Game::GetInstance()->GetInputDevice()->MouseMove.AddRaw(this, &FPSCameraController::MouseEventHandler);
}

void FPSCameraController::Update(float deltaTime)
{
	Vector3 cameraPos = Game::GetInstance()->GetCamera()->position;
	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);

	if (Game::GetInstance()->GetCamera()->isPerspectiveProjection)
	{
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
		{
			cameraPos += cameraSpeed * deltaTime * Vector3::Transform(Vector3::Right, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
		{
			cameraPos += cameraSpeed * deltaTime * Vector3::Transform(Vector3::Left, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
		{
			cameraPos -= cameraSpeed * deltaTime * Vector3::Transform(Vector3::Forward, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
		{
			cameraPos -= cameraSpeed * deltaTime * Vector3::Transform(Vector3::Backward, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::Space))
		{
			cameraPos += cameraSpeed * deltaTime * Vector3::Transform(Vector3::Up, rotationMatrix);;
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::LeftShift))
		{
			cameraPos += cameraSpeed * deltaTime * Vector3::Transform(Vector3::Down, rotationMatrix);;
		}
	}

	Vector3 cameraTarget = cameraPos + Vector3::Transform(Vector3::Backward, rotationMatrix);

	Game::GetInstance()->GetCamera()->target = cameraTarget;
	Game::GetInstance()->GetCamera()->position = cameraPos;
}

void FPSCameraController::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData)
{
	yaw   -= mouseData.Offset.x * cameraRotationSpeed;
	pitch += mouseData.Offset.y * cameraRotationSpeed;

	if (pitch >   DirectX::XM_PIDIV2 - 0.01) { pitch =   DirectX::XM_PIDIV2 - 0.01; }
	if (pitch < - DirectX::XM_PIDIV2 + 0.01) { pitch = - DirectX::XM_PIDIV2 + 0.01; }

	Game::GetInstance()->GetCamera()->fovAngle -= mouseData.WheelDelta * cameraFOVSpeed;
	if (Game::GetInstance()->GetCamera()->fovAngle > DirectX::XM_PI - DirectX::XM_PIDIV4) { Game::GetInstance()->GetCamera()->fovAngle = DirectX::XM_PI - DirectX::XM_PIDIV4; }
	if (Game::GetInstance()->GetCamera()->fovAngle < DirectX::XM_PIDIV4)                  { Game::GetInstance()->GetCamera()->fovAngle = DirectX::XM_PIDIV4; }
}