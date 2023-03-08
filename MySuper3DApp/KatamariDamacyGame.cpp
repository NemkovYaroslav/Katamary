#include "KatamariDamacyGame.h"
#include "DebugObject.h"
#include "KatamariObject.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name, int clientWidth, int clientHeight) : Game(name, clientWidth, clientHeight)
{
	Game::CreateInstance(name, clientWidth, clientHeight);
	Initialize();
}

void KatamariDamacyGame::Initialize()
{
	DebugObject* grid = new DebugObject();
	grid->CreateGrid(20, 1.0f, Color(1.0f, 0.5f, 1.0f, 1.0f));
	Game::GetInstance()->AddGameObject(grid);

	KatamariObject* sun = new KatamariObject();
	sun->CreateSphere(1.0f);
	sun->SetPosition(Vector3::UnitY);
	sun->rotationAxis = Vector3::UnitX;
	sun->rotationSpeed = 1;

	Game::GetInstance()->AddGameObject(sun);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}