#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include "item_physics.h"

class ItemInputComponent : public InputComponent
{
	public:
			ItemInputComponent(ItemPhysicsComponent* physics);
			virtual void Update(GameEntity& entity, World& world);

			void PlantItem(World& world);

		private:

			ItemPhysicsComponent* m_ItemPhysics;
};

#endif