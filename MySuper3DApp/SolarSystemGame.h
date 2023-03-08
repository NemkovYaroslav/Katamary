#pragma once
#include "Game.h"

class Planet;

class SolarSystemGame : public Game
{
public:

	SolarSystemGame(LPCWSTR name, int clientWidth, int clientHeight);

	void Initialize();
	void Run();

};