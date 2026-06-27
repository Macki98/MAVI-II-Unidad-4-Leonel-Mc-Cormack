#include "Ball.h"

 /*
	Establecemos como van a ser las propiedades del cuerpo
	Pasamos como parametro el mundo en el cual se va a crear
 */
Ball::Ball(b2World* _world, float _x, float _y)
{
	isDestroyed = false;

	radius = 10.0f;
	color = Fade(SKYBLUE, 0.95f);

	// 1. Definir tipo de cuerpo
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(_x, _y);
	ballBody = _world->CreateBody(&bodyDef);

	// 2. Definir la forma del cuerpo
	b2CircleShape ballShape;
	ballShape.m_radius = radius;

	// 3. Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &ballShape;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;
	ballBody->SetGravityScale(0.0f);
	ballBody->CreateFixture(&fixtureDef);

	// 4. Data
	BodyData* data = new BodyData();
	data->tag = BodyTag::Ball;
	data->objetcPtr = this;
	ballBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(data);

}

Ball::~Ball()
{
	BodyData* data = reinterpret_cast<BodyData*>(ballBody->GetUserData().pointer);
	delete data;

	ballBody->GetWorld()->DestroyBody(ballBody);
}

void Ball::Draw(Texture2D _tex)
{

	b2Vec2 pos = ballBody->GetPosition();
	float angle = ballBody->GetAngle() * RAD2DEG;

	Rectangle source = { 0.0f,0.0f,(float)_tex.width, (float)_tex.height };
	Rectangle dest = { pos.x,pos.y, radius * 2, radius * 2 };

	Vector2 origin = { radius,radius };

	DrawTexturePro(_tex, source, dest, origin, angle, WHITE);

}

void Ball::SetDestroyed(bool _state)
{
	isDestroyed = _state;
}

bool Ball::IsDestroyed() const
{
	return isDestroyed;
}

b2Body* Ball::GetBody() const
{
	return ballBody;
}