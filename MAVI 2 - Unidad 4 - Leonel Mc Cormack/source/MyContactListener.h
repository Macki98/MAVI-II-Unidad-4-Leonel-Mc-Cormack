#pragma once

#include <box2d.h>
#include "BodyData.h"
#include "Target.h"
#include "Ball.h"

class MyContactListener : public b2ContactListener
{
private:

	// CTC: CheckTargetCollision. Se analiza la combinacion ball&&target || target&&ball
	bool CTC(BodyData* a, BodyData* b,
		BodyTag tag1, BodyTag tag2)
	{
		return (a->tag == tag1 && b->tag == tag2)
			|| (a->tag == tag2 && b->tag == tag1);
	}

	// PTC: ProcessTargetCollision. Se registra el evento isDestroyed = true;
	void PTC(BodyData* a, BodyData* b)
	{
		Ball* realProjectile = reinterpret_cast<Ball*>((a->tag == BodyTag::Ball ? a : b)->objetcPtr);
		Target* realTarget = reinterpret_cast<Target*>((a->tag == BodyTag::Target ? a : b)->objetcPtr);
		
		realProjectile->SetDestroyed(true);
		realTarget->SetDestroyed(true);
	}

	// PDP: ProcessDeadProjectile. Se registra el evento isDestroyed = true;
	void PDP(BodyData* a, BodyData* b)
	{
		BodyData* projData = (a->tag == BodyTag::Ball) ? a : b;
		Ball* realProj = reinterpret_cast<Ball*>(projData->objetcPtr);

		realProj->SetDestroyed(true);
	}

	// PET: ProcessEscapeTarget. Se registra el evento escaped = true;
	void PET(BodyData* a, BodyData* b)
	{
		BodyData* targetData = (a->tag == BodyTag::Target) ? a : b;
		Target* realTarget = reinterpret_cast<Target*>(targetData->objetcPtr);

		realTarget->SetDestroyed(true);
		realTarget->SetEscaped(true);
		
		 
	}

public:

	void BeginContact(b2Contact* contact) override
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();

		BodyData* dataA = reinterpret_cast<BodyData*>(bodyA->GetUserData().pointer);
		BodyData* dataB = reinterpret_cast<BodyData*>(bodyB->GetUserData().pointer);

		if (!dataA || !dataB) return;
		
		// 1. Projectil vs Target
		if (CTC(dataA,dataB,BodyTag::Ball,BodyTag::Target))
		{
			PTC(dataA, dataB);
			return;
		}

		// 2. Projectile vs DeadZone (Limites de la pantalla)
		if (CTC(dataA,dataB,BodyTag::Ball, BodyTag::DeadZone))
		{
			PDP(dataA, dataB);
			return;
		}

		// 3. Projectile vs Piso
		if (CTC(dataA, dataB, BodyTag::Ball, BodyTag::Floor))
		{
			PDP(dataA, dataB);
			return;
		}

		// 4. Target vs EnemyDeadZone(escapa de la pantalla por el limite izq)
		if (CTC(dataA, dataB, BodyTag::Target, BodyTag::EnemyDeadZone)) 
		{
			PET(dataA, dataB);
			return;
		}
	}
};
