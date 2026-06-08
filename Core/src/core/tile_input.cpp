#include "tile_input.h"
#include "input/input.h"
#include <iostream>

void TileInputComponent::Update(GameEntity& entity, World& world)
{
	if (Input::IsMousePressed())
	{
		if(entity.IsSelected(Input::GetCursorPosition()))
		{
		   // std::cout<< "entidad seleccionada : r:" << entity.m_Color.x << " g:" << entity.m_Color.y << " a:" << entity.m_Color.z << std::endl;
		   std::cout<< "Tile Fila :" << entity.m_CellGrid.row << " Columna : " <<  entity.m_CellGrid.col << std::endl;
		}
	}
}
