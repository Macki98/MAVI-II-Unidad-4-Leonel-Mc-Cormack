#pragma once
#include "raylib.h"
class Menu
{
private:
	bool startGame;

public:

	Menu();
	~Menu();

	void Update();
	void Draw();

	bool StartGame() const;

};

