#include "GameController.h"

GameController::GameController()
{
	// Creamos la pantalla y establemecemos el FrameRate
	const int screenWidth = 1000;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 4 - Leonel Mc Cormack");
	SetTargetFPS(60);

	currentState = GameState::MainMenu;
	mainMenu = new Menu();
	gameLevel = nullptr;
}

GameController::~GameController() 
{	
	if (mainMenu) delete mainMenu;
	if (gameLevel) delete gameLevel;

	CloseWindow();
	
}

// Loop principal que se ejecutara hasta cerrar la ventana
void GameController::RunMainLoop()
{
	while (!WindowShouldClose())
	{
		Events();
		Update();
		Draw();
	}
}

void GameController::Events()
{

}

void GameController::Update()
{

	switch (currentState)
	{
		case GameState::MainMenu:
			if (mainMenu)
			{
				mainMenu->Update();

				if (mainMenu->StartGame())
				{
					gameLevel = new Level((float)GetScreenWidth(), (float)GetScreenHeight());
			
					currentState = GameState::InGame;

					delete mainMenu;
					mainMenu = nullptr;
				}
			}
		break;

		case GameState::InGame:
			if (gameLevel)
			{
				gameLevel->Update();

				if (gameLevel->IsFinished())
				{
					delete gameLevel;
					gameLevel = nullptr;
				}
			}
		break;
	}
}

void GameController::Draw()
{

	BeginDrawing();
	
	switch (currentState)
	{
		case GameState::MainMenu:
			if (mainMenu) mainMenu->Draw();
			break;

		case GameState::InGame:
			if (gameLevel) gameLevel->Draw();
			break;
	}

	EndDrawing();
}

