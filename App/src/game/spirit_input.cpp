#include "spirit_input.h"
#include <core/input/input.h>
#include <iostream>

void SpiritInputComponent::Update(GameEntity& entity, World& world)
{
	if (Input::IsMousePressed())
	{
		if(entity.IsSelected(Input::GetCursorPosition()))
		{
		   // std::cout<< "Enemigo Fila :" << entity.m_CellGrid.row << " Columna : " <<  entity.m_CellGrid.col << std::endl;
			entity.m_Tile->m_IsEntityPlanted = false;
			world.RemoveEntity(&entity);
		}
	}

}
