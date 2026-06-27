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
					lastResults.finalScore = gameLevel->GetScore();
					lastResults.enemiesKilled = gameLevel->GetEnemiesKilled();
					lastResults.totalEnemies = gameLevel->GetTotalEnemies();
					
					delete gameLevel;
					gameLevel = nullptr;
					
					currentState = GameState::EndScreen;
				}
			}
		break;

		case GameState::EndScreen:
			UpdateEndScreen();
			break;
	}
}

void GameController::UpdateEndScreen()
{
	if (IsKeyPressed(KEY_R))
	{
		gameLevel = new Level((float)GetScreenWidth(), (float)GetScreenHeight());
		currentState = GameState::InGame;
	}

	if (IsKeyPressed(KEY_M))
	{
		mainMenu = new Menu();
		currentState = GameState::MainMenu;
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

		case GameState::EndScreen:
			DrawEndScreen();
			break;
	}

	EndDrawing();
}

void GameController::DrawEndScreen()
{
	ClearBackground(MAROON);

	
	DrawText("PARTIDA FINALIZADA", GetScreenWidth() / 2 - MeasureText("PARTIDA FINALIZADA", 40) / 2, 120, 40, RAYWHITE);

	
	DrawText(TextFormat("PUNTAJE FINAL: %05d", lastResults.finalScore), GetScreenWidth() / 2 - MeasureText("PUNTAJE FINAL: 00000", 25) / 2, 220, 25, LIGHTGRAY);

	
	const char* enemiesKilled = TextFormat("ENEMIGOS ELIMINADOS: %d / %d", lastResults.enemiesKilled, lastResults.totalEnemies);
	DrawText(enemiesKilled, GetScreenWidth() / 2 - MeasureText(enemiesKilled, 25) / 2, 270, 25, LIGHTGRAY);

	
	DrawText("Presiona [R] para Volver a Jugar", GetScreenWidth() / 2 - MeasureText("Presiona [R] para Volver a Jugar", 20) / 2, 400, 20, RAYWHITE);
	DrawText("Presiona [M] para ir al Menu Principal", GetScreenWidth() / 2 - MeasureText("Presiona [M] para ir al Menu Principal", 20) / 2, 440, 20, GRAY);
	DrawText("Presiona [ESC] para Salir del Juego", GetScreenWidth() / 2 - MeasureText("Presiona [ESC] para Salir del Juego", 20) / 2, 480, 20, DARKGRAY);
}

