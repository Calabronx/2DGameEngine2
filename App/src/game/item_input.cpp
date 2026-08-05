#include "item_input.h"
#include <core/input/input.h>
#include <iostream>

ItemInputComponent::ItemInputComponent(ItemPhysicsComponent* physics)
{
}

void ItemInputComponent::Update(GameEntity& entity, World& world)
{
	if (Input::IsMousePressed())
	{
		if(entity.IsSelected(Input::GetCursorPosition()))
		{
		   // std::cout<< "Item Fila :" << entity.m_CellGrid.row << " Columna : " <<  entity.m_CellGrid.col << std::endl;
		   std::cout<< "Item Clickeado" << std::endl;
		   // world.RemoveEntity(&entity);
		}
	}
}
