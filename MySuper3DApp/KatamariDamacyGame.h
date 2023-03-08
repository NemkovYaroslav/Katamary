#pragma once
#include "Game.h"

class Planet;

class KatamariDamacyGame : public Game
{
public:

	KatamariDamacyGame(LPCWSTR name, int clientWidth, int clientHeight);

	void Initialize();
	void Run();
};
