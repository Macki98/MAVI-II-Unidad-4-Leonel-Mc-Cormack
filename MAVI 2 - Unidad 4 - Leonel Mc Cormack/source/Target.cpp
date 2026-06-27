#include "Target.h"

Target::Target(b2World* _world, float _x, float _y, float _width, float _height, Color _color)
{

	size = { _width, _height };
	color = _color;
	isDestroyed = false;
	escaped = false;

	// 1. Definir tipo de cuerpo
	b2BodyDef targetDef;
	targetDef.type = b2_kinematicBody;
	targetDef.position.Set(_x, _y);
	targetBody = _world->CreateBody(&targetDef);

	// 2. Definir la forma del cuerpo
	b2PolygonShape targetShape;
	targetShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);

	// 3. Fixture
	b2FixtureDef targetFixture;
	targetFixture.shape = &targetShape;
	targetFixture.density = 1.0f;
	targetFixture.friction = 0.5;
	targetFixture.restitution = 0.0f;
	targetBody->CreateFixture(&targetFixture);

	targetBody->SetLinearVelocity(b2Vec2(-9000000000.0f, 0.0f));
	// 4. Data
	BodyData* data = new BodyData();
	data->tag = BodyTag::Target;
	data->objetcPtr = this;
	targetBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(data);

}

Target::~Target()
{
	BodyData* data = reinterpret_cast<BodyData*>(targetBody->GetUserData().pointer);
	delete data;

	targetBody->GetWorld()->DestroyBody(targetBody);

}

void Target::Draw(Texture2D _tex)
{

	if (isDestroyed || escaped) return;

	b2Vec2 pos = targetBody->GetPosition();
	float angle = targetBody->GetAngle() * RAD2DEG;

	Rectangle dest = { pos.x,pos.y, size.x, size.y };
	Rectangle source = { 0.0f,0.0f, (float)_tex.width, (float)_tex.height };

	Vector2 origin = { size.x / 2.0f, size.y / 2.0f };

	DrawTexturePro(_tex, source, dest, origin, angle, WHITE);

}

bool Target::IsDestroyed() const
{
	return isDestroyed;
}

void Target::SetDestroyed(bool _state)
{
	isDestroyed = _state;
}

bool Target::IsEscaped() const
{
	return escaped;
}

void Target::SetEscaped(bool _state)
{
	escaped = _state;
}
