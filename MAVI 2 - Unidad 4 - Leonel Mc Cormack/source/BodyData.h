#pragma once

#include <cstdint>

enum class BodyTag
{
	Ball,
	Target,
	Player,
	DeadZone,
	Floor
};

struct BodyData
{
	BodyTag tag; // Guardamos "que" tipo de objeto es
	void* objetcPtr; // Guardamos "quien" es el objeto
};
