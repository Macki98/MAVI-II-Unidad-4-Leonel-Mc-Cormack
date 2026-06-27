#pragma once
#include "Level.h"
#include "Menu.h"

enum class GameState
{
	MainMenu,
	InGame
};

class GameController
{
private:
	
	GameState currentState;

	Menu* mainMenu;
	Level* gameLevel;


public:

	GameController();
	~GameController();

	void RunMainLoop();

	void Events();

	void Update();
	void Draw();

};

