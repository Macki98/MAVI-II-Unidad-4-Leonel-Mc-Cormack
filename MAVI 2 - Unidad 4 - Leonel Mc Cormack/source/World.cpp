#include "World.h"

World::World() : gravity(0.0f, 9.8f), world(gravity)
{
 
}

World::~World()
{
}

// En este metodo determinamos como calcular el estado del sistema
void World::Update()
{
    world.Step(timeStep, velocityIterations, positionIterations);
}

// En este metodo creamos un cuerpo rigido (rigid body) que actua como piso para interactuar con los objetos que caen
void World::AddFloor()
{
    Vector2 floorPos = { (float)GetScreenWidth() / 2.0f,
                 (float)GetScreenHeight() - 40.0f };

    // 1. Definir tipo de cuerpo
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(floorPos.x, floorPos.y);
    b2Body* groundBody = world.CreateBody(&groundDef);

    // 2. Definir la forma del cuerpo
    b2PolygonShape groundShape;
    groundShape.SetAsBox((float)GetScreenWidth() / 2.0f, 20.0f);
    
    // 3. Fixture
    groundBody->CreateFixture(&groundShape, 0.0f);

    // 4. Data
    groundBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new BodyData{ BodyTag::Floor, nullptr });
}

void World::CreateMapBounds(float _screenWidth, float _screenHeight)
{
    // 1- DeadZone superior
    b2BodyDef topDef;
    topDef.type = b2_staticBody;
    topDef.position.Set(_screenWidth / 2.0f, -50.0f);
    b2Body* topBody = world.CreateBody(&topDef);

    b2PolygonShape topShape;
    topShape.SetAsBox(_screenWidth / 2.0f, 10.0f);

    b2FixtureDef topFixture;
    topFixture.shape = &topShape;
    topFixture.isSensor = true;
    topBody->CreateFixture(&topFixture);

    topBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new BodyData{ BodyTag::DeadZone,nullptr });

    // 2- DeadZone Lateral
    b2BodyDef offScreenDef;
    offScreenDef.type = b2_staticBody;
    offScreenDef.position.Set(_screenWidth + 50.0f,_screenHeight / 2.0f);
    b2Body* offScreenBody = world.CreateBody(&offScreenDef);

    b2PolygonShape offScreenShape;
    offScreenShape.SetAsBox(10.0f, _screenHeight / 2.0f);

    b2FixtureDef offScreenFixture;
    offScreenFixture.shape = &offScreenShape;
    offScreenFixture.isSensor = true;
    offScreenBody->CreateFixture(&offScreenFixture);

    offScreenBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new BodyData{ BodyTag::DeadZone,nullptr });

    // 3- DeadZone especifica para el enemigo
    b2BodyDef eZoneDef;
    eZoneDef.type = b2_dynamicBody;
    eZoneDef.position.Set(-50.0f, _screenHeight / 2.0f);
    eZoneDef.gravityScale = 0.0f;
    b2Body* eZoneBody = world.CreateBody(&eZoneDef);

    b2PolygonShape eZoneShape;
    eZoneShape.SetAsBox(10.0f, _screenHeight / 2.0f);

    b2FixtureDef eZoneFix;
    eZoneFix.shape = &eZoneShape;
    eZoneFix.isSensor = true;
    eZoneBody->CreateFixture(&eZoneFix);

    eZoneBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new BodyData{ BodyTag::EnemyDeadZone, nullptr });
}

void World::Draw()
{
    DrawRectangle(0, GetScreenHeight() - 60, GetScreenWidth(), 40, Fade(DARKGREEN, 0.7f));
}

b2World* World::GetB2World()
{
    return &world;
}
