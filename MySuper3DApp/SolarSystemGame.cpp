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

	SceneObject* sun = new SceneObject();
	//sun->parent = nullptr;
	sun->CreateSphere(1.0f);
	sun->SetPosition(Vector3(0, 0, 0));
	sun->rotationAxis = Vector3(0, 1, 0);
	sun->orbitSpeed = 0.2f;
	sun->rotationSpeed = 1;

	SceneObject* mercury = new SceneObject(sun);
	//mercury->parent = sun;
	mercury->CreateSphere(0.3f);
	mercury->SetPosition(Vector3(1, 0, 1) * 1.5);
	mercury->rotationAxis = Vector3(0, 1, 0);
	mercury->orbitAxis = Vector3(0, 1, 0);
	mercury->orbitSpeed = 0.3f;
	mercury->rotationSpeed = 1;

	SceneObject* venus = new SceneObject(sun);
	//venus->parent = sun;
	venus->CreateSphere(0.4f);
	venus->SetPosition(Vector3(1, 0, 1) * 3);
	venus->rotationAxis = Vector3(0, 1, 0);
	venus->orbitAxis = Vector3(0, 1, 0);
	venus->orbitSpeed = 0.4f;
	venus->rotationSpeed = 1;

	SceneObject* earth = new SceneObject(sun);
	//earth->parent = sun;
	earth->CreateSphere(0.5f);
	earth->SetPosition(Vector3(1, 0, 1) * 4.5);
	earth->rotationAxis = Vector3(0, 1, 0);
	earth->orbitAxis = Vector3(0, 1, 0);
	earth->orbitSpeed = 0.2f;
	earth->rotationSpeed = 1;

	SceneObject* moon = new SceneObject(earth);
	//moon->parent = earth;
	moon->CreateSphere(0.15f);
	moon->SetPosition(Vector3(1, 0, 1) * 0.5);
	moon->rotationAxis = Vector3(0, 1, 0);
	moon->orbitAxis = Vector3(0, 1, 0);
	moon->orbitSpeed = 1.0f;
	moon->rotationSpeed = 5;

	SceneObject* mars = new SceneObject(sun);
	//mars->parent = sun;
	mars->CreateSphere(0.4f);
	mars->SetPosition(Vector3(1, 0, 1) * 6);
	mars->rotationAxis = Vector3(0, 1, 0);
	mars->orbitAxis = Vector3(0, 1, 0);
	mars->orbitSpeed = 0.3f;
	mars->rotationSpeed = 1;

	SceneObject* marsSat1 = new SceneObject(mars);
	//marsSat1->parent = mars;
	marsSat1->CreateSphere(0.12f);
	marsSat1->SetPosition(Vector3(1, 0, 1) * 0.5);
	marsSat1->rotationAxis = Vector3(0, 1, 0);
	marsSat1->orbitAxis = Vector3(1, 0, 0);
	marsSat1->orbitSpeed = 8.0f;
	marsSat1->rotationSpeed = 1;

	SceneObject* marsSat2 = new SceneObject(mars);
	//marsSat2->parent = mars;
	marsSat2->CreateSphere(0.2f);
	marsSat2->SetPosition(Vector3(1, 0, 1) * 0.75);
	marsSat2->rotationAxis = Vector3(0, 1, 0);
	marsSat2->orbitAxis = Vector3(0, 1, 0);
	marsSat2->orbitSpeed = 6.0f;
	marsSat2->rotationSpeed = 1;

	SceneObject* jupiter = new SceneObject(sun);
	//jupiter->parent = sun;
	jupiter->CreateSphere(0.8f);
	jupiter->SetPosition(Vector3(1, 0, 1) * 7.5);
	jupiter->rotationAxis = Vector3(0, 1, 0);
	jupiter->orbitAxis = Vector3(0, 1, 0);
	jupiter->orbitSpeed = 0.4f;
	jupiter->rotationSpeed = 1;

	SceneObject* saturn = new SceneObject(sun);
	//saturn->parent = sun;
	saturn->CreateCube(0.3f);
	saturn->SetPosition(Vector3(1, 0, 1) * 9);
	saturn->rotationAxis = Vector3(1, 1, 0);
	saturn->orbitAxis = Vector3(0, 1, 0);
	saturn->orbitSpeed = 0.2f;
	saturn->rotationSpeed = 1;

	SceneObject* saturnSat1 = new SceneObject(saturn);
	//saturnSat1->parent = saturn;
	saturnSat1->CreateCube(0.15f);
	saturnSat1->SetPosition(Vector3(1, 0, 1) * 0.7);
	saturnSat1->rotationAxis = Vector3(0, 1, 0);
	saturnSat1->orbitAxis = Vector3(0, 1, 0);
	saturnSat1->orbitSpeed = 7.0f;
	saturnSat1->rotationSpeed = 1;

	SceneObject* saturnSat2 = new SceneObject(saturn);
	//saturnSat2->parent = saturn;
	saturnSat2->CreateCube(0.15f);
	saturnSat2->SetPosition(Vector3(1, 0, 1) * 1.1);
	saturnSat2->rotationAxis = Vector3(0, 1, 0);
	saturnSat2->orbitAxis = Vector3(1, 1, 0);
	saturnSat2->orbitSpeed = 1.5f;
	saturnSat2->rotationSpeed = 1;

	SceneObject* saturnSat3 = new SceneObject(saturn);
	//saturnSat3->parent = saturn;
	saturnSat3->CreateCube(0.15f);
	saturnSat3->SetPosition(Vector3(1, 0, 1) * 1.5);
	saturnSat3->rotationAxis = Vector3(0, 1, 0);
	saturnSat3->orbitAxis = Vector3(0, 1, 1);
	saturnSat3->orbitSpeed = 2.0f;
	saturnSat3->rotationSpeed = 1;

	Game::GetInstance()->AddGameObject(sun);
	Game::GetInstance()->AddGameObject(mercury);
	Game::GetInstance()->AddGameObject(venus);
	Game::GetInstance()->AddGameObject(earth);
	Game::GetInstance()->AddGameObject(moon);
	Game::GetInstance()->AddGameObject(mars);
	Game::GetInstance()->AddGameObject(marsSat1);
	Game::GetInstance()->AddGameObject(marsSat2);
	Game::GetInstance()->AddGameObject(jupiter);
	Game::GetInstance()->AddGameObject(saturn);
	Game::GetInstance()->AddGameObject(saturnSat1);
	Game::GetInstance()->AddGameObject(saturnSat2);
	Game::GetInstance()->AddGameObject(saturnSat3);
}

void SolarSystemGame::Run()
{
	Game::GetInstance()->Run();
}