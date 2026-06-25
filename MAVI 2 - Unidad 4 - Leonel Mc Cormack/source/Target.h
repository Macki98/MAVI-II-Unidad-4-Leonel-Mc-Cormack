#pragma once
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include"BodyData.h"

class Target
{

private:

	b2Body* targetBody;
	Vector2 size;
	Color color;
	bool isDestroyed;

public:

	Target(b2World* _world, float _x, float _y, float _width, float _height, Color _color );
	~Target();

	void Draw();

	bool IsDestroyed();
	void SetDestroyed(bool _state);
	b2Body* GetBody();


};

