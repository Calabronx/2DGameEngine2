#pragma once
#include "data/entities/entity.h"
#ifndef TILE_INPUT
#define TILE_INPUT

class TileInputComponent : public InputComponent
{
	public:
		void Update(GameEntity& entity, World& world);
};

#endif
