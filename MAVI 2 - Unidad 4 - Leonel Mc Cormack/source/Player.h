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
	
	int maxAmmo;
	int currentAmmo;
	float fireForce;

public:
	Player(b2World* _world, float _x, float _y);
	~Player();

	void Update(b2World* _world, std::vector<Ball*>& bullets);
	void Draw();

	int GetCurrentAmmo() const;
	int GetMaxAmmo() const;
	void ResetAmmo();

	void Shoot();
};

