#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "BodyData.h"

class Ball
{
private:
	
	// Definimos las propiedades iniciales del cuerpo
	b2Body* ballBody;
	float radius;
	Color color;
	bool isDestroyed;

public:

	Ball(b2World* _world, float _x, float _y);
	~Ball();

	void Draw();

	void SetDestroyed(bool _state);
	bool IsDestroyed() const;

	b2Body* GetBody() const;

};

