#include "GameController.h"

GameController::GameController()
{
	// Creamos la pantalla y establemecemos el FrameRate
	const int screenWidth = 1000;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 1 - Leonel Mc Cormack");
	SetTargetFPS(60);

	// Creamos el mundo
	physicsWorld = new World;

	// Establecemos los limites del mundo
	physicsWorld->AddFloor();
	physicsWorld->CreateMapBounds((float)GetScreenWidth(), (float)GetScreenHeight());
	
	// Creamos y asociamos el Listener al mundo fisico
	contactListener = new MyContactListener();
	physicsWorld->GetB2World()->SetContactListener(contactListener);

	player = new Player(physicsWorld->GetB2World(), 50.0f, 500.0f);

	targets.push_back(new Target(physicsWorld->GetB2World(), 800.0f, 500.0f, 20.0f, 30.0f, RED));

}

GameController::~GameController() 
{
	delete player;
	for (auto b : bullets) delete b;
	for (auto t : targets) delete t;
	
	delete contactListener;

	delete physicsWorld;
}

// Loop principal que se ejecutara hasta cerrar la ventana
void GameController::RunMainLoop()
{
	
	while (!WindowShouldClose())
	{
		Events();
		UpdateGame();
		DrawGame();
	}

	CloseWindow();
}

void GameController::Events()
{

}

void GameController::UpdateGame()
{

	physicsWorld->Update();

	player->Update(physicsWorld->GetB2World(), bullets);

	// Limpieza de Obejetivos
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i]->IsDestroyed())
		{
			std::cout << "Target Impactado" << std::endl;

			delete targets[i];
			targets.erase(targets.begin() + i);
			i--;
		}
	}

	// Limpieza de Proyectiles
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->IsDestroyed())
		{
			std::cout << "Bala destruida" << std::endl;

			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void GameController::DrawGame()
{

	BeginDrawing();
	ClearBackground(background);

	physicsWorld->Draw();

	player->Draw();

	for (Ball* b : bullets)
	{
		b->Draw();
	}

	for (Target* t : targets)
	{
		t->Draw();
	}

	DrawText("C: Crear Bola | Flechas: Rotar | ESPACIO: Lanzar caja", 10, 10, 20, DARKGRAY);
	DrawText(TextFormat("Angulo actual: %.2f", currentAngle), 10, 40, 20, BLUE);

	EndDrawing();
}

