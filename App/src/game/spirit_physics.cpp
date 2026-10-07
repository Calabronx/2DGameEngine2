#include "spirit_physics.h"
#include <Core/application.h>
#include <cassert>

void SpiritPhysicsComponent::Update(GameEntity& entity, World& world)
{
	for (auto* otherEntity : world.GetEntities())
	{
		if (otherEntity->m_Id != ITEM)
			continue;


		bool lightUp = otherEntity->m_CellGrid.col == entity.m_CellGrid.col - 1 && otherEntity->m_CellGrid.row == entity.m_CellGrid.row;
		bool lightDown = otherEntity->m_CellGrid.col == entity.m_CellGrid.col + 1 && otherEntity->m_CellGrid.row == entity.m_CellGrid.row;
		bool lightLeft = otherEntity->m_CellGrid.col == entity.m_CellGrid.col && otherEntity->m_CellGrid.row == entity.m_CellGrid.row - 1;
		bool lightRight = otherEntity->m_CellGrid.col == entity.m_CellGrid.col && otherEntity->m_CellGrid.row == entity.m_CellGrid.row + 1;
		if (lightDown || lightUp || lightLeft || lightRight)
		{
			if (entity.m_Tile == nullptr)
				return;
			
			assert(entity.m_Tile != nullptr);
			entity.m_Tile->m_IsEntityPlanted = false;
			entity.m_EntityLifeCounter--;
			if (entity.m_EntityLifeCounter <= 0)
			{
				world.RemoveEntity(&entity);
			}
		}
	}

	entity.m_Position.x +=  entity.m_Velocity.x;
    entity.m_Position.y +=  entity.m_Velocity.y;
}
