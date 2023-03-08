#pragma once
#include "includes.h"

class DisplayWin32;
class GameObject;
class RenderSystem;
class InputDevice;
class Camera;
class FPSCameraController;
class TPSCameraController;

class Game
{
private:

	LPCWSTR	name;
	int clientWidth;
	int clientHeight;

	std::shared_ptr<std::chrono::time_point<std::chrono::steady_clock>> startTime;
	std::shared_ptr<std::chrono::time_point<std::chrono::steady_clock>> prevTime;
	HRESULT res;
	float totalTime;
	float deltaTime;
	unsigned int frameCount;

	std::shared_ptr<FPSCameraController> fpsCameraController;
	std::shared_ptr<TPSCameraController> tpsCameraController;
	bool wasProjectionKeyDown = false;
	bool wasCameraControllerKeyDown = false;

protected:

	Game(LPCWSTR name, int clientWidth, int clientHeight);
	static Game* instance;

	std::shared_ptr<DisplayWin32> display;
	std::shared_ptr<RenderSystem> render;
	std::shared_ptr<InputDevice>  inputDevice;
	std::shared_ptr<Camera>       camera;

	virtual void DestroyResources();
	virtual void Draw();
	virtual void Initialize();
	virtual void PrepareResources();
	virtual void Update();
	virtual void UpdateInternal();

public:

	std::vector<GameObject*> GameObjects;
	Game(const Game&) = delete;
	void operator = (const Game&) = delete;
	virtual ~Game() = default;

	static Game* CreateInstance(LPCWSTR name, int screenWidth, int screenHeight);
	static Game* GetInstance();

	void Run();

	void AddGameObject(GameObject* gameObject);

	std::shared_ptr<RenderSystem> GetRenderSystem();
	std::shared_ptr<DisplayWin32> GetDisplay();
	std::shared_ptr<InputDevice>  GetInputDevice();
	std::shared_ptr<Camera>       GetCamera();

	LRESULT MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);