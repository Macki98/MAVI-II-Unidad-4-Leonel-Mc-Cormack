#include "Menu.h"

Menu::Menu()
{
	startGame = false;
}

Menu::~Menu()
{
}

void Menu::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		startGame = true;
	}
}

void Menu::Draw()
{
	ClearBackground(BLACK);

	DrawText("LLAMADO AL DEBER", GetScreenWidth() / 2 - MeasureText("LLAMADO AL DEBER", 40) / 2, 200, 40, RAYWHITE);

	DrawText("Presiona [ENTER] para iniciar la partida", GetScreenWidth() / 2 - MeasureText("Presiona [ENTER] para iniciar la partida", 20) / 2, 350, 20, LIGHTGRAY);

	DrawText("Utiliza [CLICK IZQUIERDO] para disparar y [CLICK DERECHO] para apuntar", GetScreenWidth() / 2 - MeasureText("Utiliza [CLICK IZQUIERDO] para disparar y [CLICK DERECHO] para apuntar", 20) / 2, 500, 20, LIGHTGRAY);


}

bool Menu::StartGame() const
{
	return startGame;
}
