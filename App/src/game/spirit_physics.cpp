#include "spirit_physics.h"

void SpiritPhysicsComponent::Update(GameEntity& entity, World& world)
{
	for (auto* otherEntity : world.GetEntities())
	{
		if (otherEntity->m_Id != ITEM)
			continue;

		bool lightDown = otherEntity->m_CellGrid.col == entity.m_CellGrid.col + 1 && otherEntity->m_CellGrid.row == entity.m_CellGrid.row;
		bool lightRight = otherEntity->m_CellGrid.col == entity.m_CellGrid.col && otherEntity->m_CellGrid.row == entity.m_CellGrid.row + 1;
		bool lightUp = otherEntity->m_CellGrid.col == entity.m_CellGrid.col + 1 && otherEntity->m_CellGrid.row == entity.m_CellGrid.row + 1;
		bool lightLeft = otherEntity->m_CellGrid.col == entity.m_CellGrid.col && otherEntity->m_CellGrid.row == entity.m_CellGrid.row + 1;

		if (lightDown || lightRight || lightUp)
		{
			entity.m_Tile->m_IsEntityPlanted = false;
			entity.m_EntityLifeCounter--;
			if (entity.m_EntityLifeCounter == 0)
			{
				world.RemoveEntity(&entity);
			}
		}
	}
}
