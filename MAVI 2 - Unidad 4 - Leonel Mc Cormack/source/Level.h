#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "World.h"
#include "MyContactListener.h"
#include "Ball.h"
#include "Target.h"
#include "Player.h"

enum class GameplayState
{
	Playing,
	Reloading,
	Victory
};

class Level
{
private:

	GameplayState currentState;

	World* physicsWorld;
	MyContactListener* contactListener;

	Player* player;
	std::vector<Ball*> bullets;
	std::vector<Target*> targets;

	bool isFinished;

	int score;
	
	float spawnTimer;
	float intervalSpawn;
	int totalTargets;
	int enemiesSpawned;

	float reloadTimer;
	float reloadTime;

	Color background = { 110, 100, 215, 255 };

public:

	Level(float _screenWidht, float _screenHeight);
	~Level();

	void Update();
	void Draw();

	void SpawnTimer();
	void SpawnEnemies();
	void CleanEnemiesAndProjectiles();

	bool IsFinished() const;

};

