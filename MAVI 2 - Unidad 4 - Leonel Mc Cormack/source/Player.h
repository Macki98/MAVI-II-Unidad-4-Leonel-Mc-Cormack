#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "Ball.h"
#include "BodyData.h"

class Player
{
private:
	b2Body* playerBody;
	Vector2 size;
	
	float fireForce;

public:
	Player(b2World* _world, float _x, float _y);
	~Player();

	void Update(b2World* _world, std::vector<Ball*>& bullets);
	void Draw();

	Vector2 GetPosition();
};

