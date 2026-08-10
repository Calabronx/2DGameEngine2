#include "spirit_physics.h"

void SpiritPhysicsComponent::Update(GameEntity& entity, World& world)
{
	for (auto i = 0; i < world.GetEntities().size(); i++)
	{
		
		// if (world.GetEntities()[i]->m_Id == ITEM && entity.m_CellGrid.row == world.GetEntities()[i]->m_CellGrid.row 
		// 	&& entity.m_CellGrid.col + 1 == world.GetEntities()[i]->m_CellGrid.col)
		// {
		// 	// VELA ESTA ABAJO EN LA COORDENADA, MORIR();

		// 		int d = 2;
		// }

		for (auto* otherEntity : world.GetEntities())
		{
			if (otherEntity->m_Id != ITEM)
				continue;

			bool sameColumn = otherEntity->m_CellGrid.col == entity.m_CellGrid.col;
			bool lightDown = otherEntity->m_CellGrid.row == entity.m_CellGrid.row + 1;

			if (sameColumn && lightDown)
			{
				world.RemoveEntity(&entity);
			}
		}

	}
}
