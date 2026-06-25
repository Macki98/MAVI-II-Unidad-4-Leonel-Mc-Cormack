#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include <iostream>
#include "World.h"
#include "MyContactListener.h"
#include "Ball.h"
#include "Target.h"
#include "Player.h"


class GameController
{
private:
	
	/*
		Le damos un atributo World para crear ese mundo fisico
		y un contenedor dinamico que almacenara nuestros objetos (Box)
	*/
	World* physicsWorld;
	MyContactListener* contactListener;
	
	Player* player;

	std::vector<Ball*> bullets;
	std::vector<Target*> targets;

	// Con estas variables podemos establecer el angulo con el que se crea el objeto
	float currentAngle = 0.0f;
	const float rotationSpeed = 2.0f;

	Color background = { 110, 100, 215, 255 };

public:

	GameController();
	~GameController();

	void RunMainLoop();

	void Events();
	void UpdateGame();
	void DrawGame();

};

