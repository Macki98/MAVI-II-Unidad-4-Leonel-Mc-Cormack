#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "BodyData.h"

class World
{
private:
	/*
		Establecemos una clase World
		La misma se encarga de administrar el mundo fisico
		Para ello indicamos el vector de gravedad (gravity)
		Un mundo (world) el cual tendra los elementos necesarios
		para calcular el siguiente estado del sistema
		y como los objetos evolucionan a lo largo del tiempo
	*/
	b2Vec2 gravity;
    b2World world;

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

public:
	World();
	~World();

	void Update();
	void Draw();

	void AddFloor();
	void CreateMapBounds(float _screenWidth, float _screenHeight);
	
	// Metodo necesario para poder acceder desde el constructor de Box
	b2World* GetB2World();

};

