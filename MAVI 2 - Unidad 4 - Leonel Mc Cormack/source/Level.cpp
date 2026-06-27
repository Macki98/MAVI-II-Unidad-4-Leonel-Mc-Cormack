#include "Level.h"
#include <iostream>

Level::Level(float _screenWidth, float _screenHeight)
{
	isFinished = false;
	score = 0;
	enemiesKilled = 0;
	spawnTimer = 0.0f;
	intervalSpawn = 3.5f;
	totalTargets = 20;
	enemiesSpawned = 0;

	reloadTimer = 0.0f;
	reloadTime = 5.0f;

	playerTex = LoadTexture("Assets/player.png");
	bulletTex = LoadTexture("Assets/projectile.png");
	enemyTex = LoadTexture("Assets/enemy.png");

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

	UnloadTexture(playerTex);
	UnloadTexture(bulletTex);
	UnloadTexture(enemyTex);

	delete contactListener;
	delete physicsWorld;
}

void Level::Update()
{
	physicsWorld->Update();
	SpawnTimer();

	CleanEnemiesAndProjectiles();

	switch (currentState)
	{
		case GameplayState::Playing:

			if (player) player->Update(physicsWorld->GetB2World(), bullets);
			if (player && player->GetCurrentAmmo() == 0)
			{
				currentState = GameplayState::Reloading;
				reloadTimer = 0.0f;
			}
		break;

		case GameplayState::Reloading:

			reloadTimer += GetFrameTime();

			if (reloadTimer >= reloadTime)
			{
				player->ResetAmmo();
				currentState = GameplayState::Playing;
			}
		break;

		case GameplayState::Victory:

			isFinished = true;
		break;
	}

	
	if (enemiesSpawned >= totalTargets && targets.empty())
	{
		currentState = GameplayState::Victory;
	}

}

void Level::Draw()
{

	ClearBackground(background);

	physicsWorld->Draw();

	if (player) player->Draw(playerTex);

	for (Ball* b : bullets)
	{
		b->Draw(bulletTex);
	}

	for (Target* t : targets)
	{
		t->Draw(enemyTex);
	}
	
	DrawText(TextFormat("SCORE: %05d", score), 20, 20, 25, DARKGRAY);
	DrawText(TextFormat("TARGETS: %d", targets.size()), GetScreenWidth() - 160, 20, 25, MAROON);

	if (currentState == GameplayState::Reloading)
	{
		DrawText("RELOADING...", 20, GetScreenHeight() - 45, 25, RED);
	}
	else if (player) 
	{
		DrawText(TextFormat("AMMO: %d / %d", player->GetCurrentAmmo(), player->GetMaxAmmo()), 20, GetScreenHeight() - 45, 25, DARKGRAY);
	}

}

void Level::SpawnTimer()
{
	if (enemiesSpawned < totalTargets)
	{
		spawnTimer += GetFrameTime();

		if (spawnTimer >= intervalSpawn)
		{
			SpawnEnemies();
			spawnTimer = 0.0f;
		}
	}
}

void Level::SpawnEnemies()
{
	for (int i = 0; i < 2; i++)
	{
		float randomY = (float)GetRandomValue(80, (float)GetScreenHeight() * 0.75f);
		float spawnX = (float)GetScreenWidth() + 40.0f;

		Target* enemy = new Target(physicsWorld->GetB2World(), spawnX, randomY, 40.0f, 60.0f, RED);

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
				enemiesKilled++;
				score += 100;
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

int Level::GetScore() const
{
	return score;
}

int Level::GetTotalEnemies() const
{
	return totalTargets;
}

int Level::GetEnemiesKilled() const
{
	return enemiesKilled;
}
