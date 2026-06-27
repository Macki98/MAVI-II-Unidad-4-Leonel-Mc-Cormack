#pragma once
#include "Level.h"
#include "Menu.h"

enum class GameState
{
	MainMenu,
	InGame,
	EndScreen
};

struct GameResults
{
	int finalScore = 0;
	int enemiesKilled = 0;
	int totalEnemies = 0;
};

class GameController
{
private:
	
	GameState currentState;

	Menu* mainMenu;
	Level* gameLevel;

	GameResults lastResults;

public:

	GameController();
	~GameController();

	void RunMainLoop();

	void Events();

	void Update();
	void UpdateEndScreen();

	void Draw();
	void DrawEndScreen();
};

