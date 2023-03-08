#pragma once
#include "includes.h"

using namespace DirectX::SimpleMath;

class CameraController;

class Camera
{
protected:

	CameraController* cameraController;

public:

	CameraController* GetCameraController();
	void SetCameraController(CameraController* cameraController);

	Camera();
	void Update(float deltaTime);
	Matrix GetWorldViewProjectionMatrix(Matrix World);

	bool isPerspectiveProjection = true;
	Matrix view;
	Matrix projection;
	Vector3 position;
	Vector3 target;
	Vector3 up;
	float fovAngle = DirectX::XM_PIDIV2;
};