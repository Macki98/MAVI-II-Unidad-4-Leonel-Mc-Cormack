#include "Player.h"
#include <cmath>

Player::Player(b2World* _world, float _x, float _y)
{
	size = { 20.0f,40.0f };
	fireForce = 9000000000.0f;

	// 1. Definir el tipo de cuerpo
	b2BodyDef playerDef;
	playerDef.type = b2_dynamicBody;
	playerDef.position.Set(_x, _y);
	playerBody = _world->CreateBody(&playerDef);
	
	// 2. Definir la forma del cuerpo
	b2PolygonShape playerShape;
	playerShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);

	// 3. Fixture
	b2FixtureDef playerFixture;
	playerFixture.shape = &playerShape;
	playerFixture.density = 1.0f;
	playerFixture.friction = 0.3f;
	playerBody->CreateFixture(&playerFixture);

	// 4. Data
	BodyData* data = new BodyData();
	data->tag = BodyTag::Player;
	data->objetcPtr = this;
	playerBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(data);
}

Player::~Player()
{
	BodyData* data = reinterpret_cast<BodyData*>(playerBody->GetUserData().pointer);
	delete data;

	playerBody->GetWorld()->DestroyBody(playerBody);
}

void Player::Update(b2World* _world, std::vector<Ball*>& bullets)
{
	Vector2 mousePos = GetMousePosition();
	b2Vec2 playerPos = playerBody->GetPosition();

	Vector2 dir = { mousePos.x - playerPos.x, mousePos.y - playerPos.y };

	float large = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (large != 0.0f)
	{
		dir.x /= large;
		dir.y /= large;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		float spawnX = playerPos.x + dir.x * 25.0f;
		float spawnY = playerPos.y + dir.y * 25.0f;

		Ball* newBullet = new Ball(_world, spawnX, spawnY);

		b2Vec2 impulse(dir.x * fireForce, dir.y * fireForce);
		newBullet->GetBody()->ApplyLinearImpulseToCenter(impulse, true);
		
		bullets.push_back(newBullet);
	}
}

void Player::Draw()
{
	b2Vec2 pos = playerBody->GetPosition();
	float angle = playerBody->GetAngle() * RAD2DEG;

	Rectangle rect = { pos.x,pos.y,size.x,size.y };
	Vector2 origin = { size.x / 2.0f,size.y / 2.0f };

	DrawRectanglePro(rect, origin, angle, DARKGRAY);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector2 mousePos = GetMousePosition();
		DrawLine(pos.x, pos.y, mousePos.x, mousePos.y, RED);
		DrawCircleV(mousePos, 5.0f, RED);
	}
}
