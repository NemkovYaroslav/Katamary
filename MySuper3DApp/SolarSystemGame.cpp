#include "SolarSystemGame.h"
#include "DebugObject.h"
#include "SceneObject.h"

SolarSystemGame::SolarSystemGame(LPCWSTR name, int clientWidth, int clientHeight) : Game(name, clientWidth, clientHeight)
{
	Game::CreateInstance(name, clientWidth, clientHeight);
	Initialize();
}

void SolarSystemGame::Initialize()
{
	DebugObject* grid = new DebugObject();
	grid->CreateGrid(20, 1.0f, Color(1.0f, 0.5f, 1.0f, 1.0f));
	Game::GetInstance()->AddGameObject(grid);
}

void SolarSystemGame::Run()
{
	Game::GetInstance()->Run();
}