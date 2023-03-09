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

	KatamariObject* katamari = new KatamariObject();
	katamari->radius = katamari->katamariRadius;
	katamari->CreateSphere(katamari->katamariRadius);
	katamari->SetPosition(Vector3::UnitY);
	katamari->rotationAxis = Vector3::Zero;
	katamari->rotationSpeed = 5;
	katamari->isKatamari = true;

	KatamariObject* moon = new KatamariObject(katamari);
	moon->radius = 0.5f;
	moon->CreateSphere(moon->radius);
	moon->SetPosition(katamari->GetPosition() * 1.6f);
	moon->rotationAxis = Vector3::Zero;
	moon->rotationSpeed = 1;

	Game::GetInstance()->AddGameObject(katamari);
	Game::GetInstance()->AddGameObject(moon);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}