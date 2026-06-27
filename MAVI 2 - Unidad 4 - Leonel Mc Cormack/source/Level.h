#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "World.h"
#include "MyContactListener.h"
#include "Ball.h"
#include "Target.h"
#include "Player.h"

class Level
{
private:

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

	Color background = { 110, 100, 215, 255 };

public:

	Level(float _screenWidht, float _screenHeight);
	~Level();

	void Update();
	void Draw();

	void SpawnEnemies();
	void CleanEnemiesAndProjectiles();

	bool IsFinished() const;

};

