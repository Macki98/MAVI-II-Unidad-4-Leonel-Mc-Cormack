#include "Level.h"
#include <iostream>

Level::Level(float _screenWidth, float _screenHeight)
{
	isFinished = false;
	score = 0;

	spawnTimer = 0.0f;
	intervalSpawn = 3.5f;
	totalTargets = 20;
	enemiesSpawned = 0;

	// Creamos el mundo
	physicsWorld = new World;

	// Establecemos los limites del mundo
	physicsWorld->AddFloor();
	physicsWorld->CreateMapBounds((float)GetScreenWidth(), (float)GetScreenHeight());

	// Creamos y asociamos el Listener al mundo fisico
	contactListener = new MyContactListener();
	physicsWorld->GetB2World()->SetContactListener(contactListener);

	player = new Player(physicsWorld->GetB2World(), 50.0f, 500.0f);

}

Level::~Level()
{
	if (player) delete player;

	for (auto b : bullets) delete b;
	for (auto t : targets) delete t;

	if (physicsWorld && physicsWorld->GetB2World())
	{
		physicsWorld->GetB2World()->SetContactListener(nullptr);
	}

	delete contactListener;
	delete physicsWorld;
}

void Level::Update()
{
	physicsWorld->Update();

	player->Update(physicsWorld->GetB2World(), bullets);

	if (enemiesSpawned < totalTargets)
	{
		spawnTimer += GetFrameTime();
		
		if (spawnTimer >= intervalSpawn)
		{
			SpawnEnemies();
			spawnTimer = 0.0f;
		}
	}

	CleanEnemiesAndProjectiles();

	/*
	if (enemiesSpawned >= totalTargets && targets.empty())
	{
		isFinished = true;
	}
	*/
}

void Level::Draw()
{

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

	
	DrawText(TextFormat("SCORE: %05d", score), 20, 20, 25, DARKGRAY);

	DrawText(TextFormat("TARGETS: %d", targets.size()), GetScreenWidth() - 160, 20, 25, MAROON);

}

void Level::SpawnEnemies()
{
	for (int i = 0; i < 2; i++)
	{
		float randomY = (float)GetRandomValue(80, (float)GetScreenHeight() * 0.75f);
		float spawnX = (float)GetScreenWidth() + 40.0f;

		Target* enemy = new Target(physicsWorld->GetB2World(), spawnX, randomY, 40.0f, 40.0f, RED);

		targets.push_back(enemy);
		enemiesSpawned++;
	}
}

void Level::CleanEnemiesAndProjectiles()
{

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

	// Limpieza de Obejetivos
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i]->IsDestroyed())
		{
			if (!targets[i]->IsEscaped())
			{
				std::cout << "Target Impactado" << std::endl;
				score += 10;
			}
			else
			{
				std::cout << "Un enemigo escapo del mapa (0 puntos)." << std::endl;
			}

			delete targets[i];
			targets.erase(targets.begin() + i);
			i--;
		}
	}
}

bool Level::IsFinished() const
{
	return isFinished;
}
