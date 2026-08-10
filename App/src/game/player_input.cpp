#include "player_input.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <core/input/input.h>
#include <core/application.h>
#include "core/world.h"
#include <core/util.h>
#include "game_entity_factory.h"

namespace
{
	int g_tilePosition = 0;

	bool g_firstClick = false;
	bool g_IsMoving = false;
	bool g_Up = false;
	bool g_Down = false;
	bool g_Right = false;
	bool g_Left = false;
	bool g_Arrived = false;

	TargetCell g_Target;
};

PlayerInputComponent::PlayerInputComponent(PlayerPhysicsComponent* physics)
	: m_PlayerPhysics(physics)
{
	// inicializar esto correctamente una sola vez, con la posicion inicial del jugador
	// en el constructor
	// Esto tiene que venir de una constante, no harcodeado, cambiar
	g_Target.gridPosition.x = 8; 
	g_Target.gridPosition.y = 7;

}

void PlayerInputComponent::Update(GameEntity& entity, World& world)
{
	const float deltaTime = Engine::Application::GetDeltaTime();

	if (!g_IsMoving)
	{

		if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
			TargetCell targetTemp = {};
			targetTemp.gridPosition = { entity.m_CellGrid.row, entity.m_CellGrid.col };
			targetTemp.gridPosition.y -= 1;

			if (targetTemp.gridPosition.y <= 0)
				return;

			GetMovementCells(world, targetTemp);

			if (!targetTemp.isTarget)
				return;

			g_IsMoving = true;
			g_Up = true;
			g_Target = targetTemp;
			//g_Target.gridPosition.y -= 1;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_D))
		{
			TargetCell targetTemp = {};
			targetTemp.gridPosition = { entity.m_CellGrid.row, entity.m_CellGrid.col };
			targetTemp.gridPosition.x += 1;

			if (targetTemp.gridPosition.x >= 13)
				return;
			
			GetMovementCells(world, targetTemp);

			if (!targetTemp.isTarget)
				return;

			g_IsMoving = true;
			g_Right = true;
			g_Target = targetTemp;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_A))
		{
			TargetCell targetTemp = {};
			targetTemp.gridPosition = { entity.m_CellGrid.row, entity.m_CellGrid.col };
			targetTemp.gridPosition.x -= 1;

			if (g_Target.gridPosition.x <= 0)
				return;

			GetMovementCells(world, targetTemp);

			if (!targetTemp.isTarget)
				return;

			g_IsMoving = true;
			g_Left = true;
			g_Target = targetTemp;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_S))
		{
			TargetCell targetTemp = {};
			targetTemp.gridPosition = { entity.m_CellGrid.row, entity.m_CellGrid.col };
			targetTemp.gridPosition.y += 1;

			if (g_Target.gridPosition.y >= 15)
				return;
			
			GetMovementCells(world, targetTemp);

			if (!targetTemp.isTarget)
				return;
			
			g_IsMoving = true;
			g_Down = true;
			g_Target = targetTemp;
		}
		//std::cout << "GRID ROW: "<<  g_Target.gridPosition.x << std::endl;
		//std::cout << "GRID COL: "<<  g_Target.gridPosition.y << std::endl;
	}

	// if (g_IsMoving && !g_Target.isTarget)
	// {
	// 	GetMovementCells(world, g_Target);
	// }

	if (g_IsMoving)
	{
		glm::vec2 entityCenter = entity.GetCenter();
		glm::vec2 toTarget = g_Target.targetCenter - entityCenter;
		float distance = glm::length(toTarget);

		const float ARRIVAL_THRESHOLD = 2.0f;

		if (distance < ARRIVAL_THRESHOLD)
		{	
			entity.m_Position = g_Target.targetCenter - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f);

			entity.m_CellGrid.col = g_Target.gridPosition.y;
			entity.m_CellGrid.row = g_Target.gridPosition.x;

			entity.m_Velocity.x = 0;
			entity.m_Velocity.y = 0;

			g_IsMoving = false;
			g_Up = false;
			g_Down = false;
			g_Right = false;
			g_Left = false;
			g_Target.isTarget = false;
			g_Arrived = false;
			return;
		}

		glm::vec2 direction = toTarget / distance;

		entity.m_Velocity.x = direction.x * WALK_ACCELERATION * deltaTime;
		entity.m_Velocity.y = direction.y * WALK_ACCELERATION * deltaTime;
	}

	if (Input::IsMousePressed())
	{
		if (g_firstClick)
			return;
		
		glm::vec2 cursorPos = Input::GetCursorPosition();
		//std::cout << "mouse x: " << cursorPos.x << " mouse y: " << cursorPos.y << std::endl;
		bool clicked = false;
		for (auto i = 0; i < world.GetEntities().size() && !g_firstClick; i++)
		{
			if (world.GetEntities()[i]->IsSelected(cursorPos)) // movimento del jugador en las tiles, deberia identificar si es una Tile real
			{
				GameEntity* tile = world.GetEntities()[i];
				// falta validar correctamente la interaccion con las entidades del mundo, poder obtener su pointer
				if (tile->m_Id == WALL || tile->m_IsEntityPlanted) // hacer una funcion que valide si esta tile base tiene algun objeto
				{
					return;
				} else if (tile->m_Id == ITEM)
				{
					std::cout << "ANTORCHA PRESIONADA! " << world.GetEntities()[i]->m_Id << std::endl;
					return;
				}

				g_firstClick = true;
				std::cout << "jugador toco la entidad: " << world.GetEntities()[i]->m_Id << std::endl;
				std::cout << "GRID ROW: "<<  world.GetEntities()[i]->m_CellGrid.row << std::endl;
				std::cout << "GRID COL: "<<  world.GetEntities()[i]->m_CellGrid.col << std::endl;
				// setear el item en esta tile
				PlantItem(world, ITEM, tile);
			}
		}
	}
	else
	{
		g_firstClick = false;
	}
	// std::cout << "velocity player X: " << entity.m_Velocity.x << " Y: " << entity.m_Velocity.y << " " << std::endl;
}

void PlayerInputComponent::SetDirection()
{
}

void PlayerInputComponent::GetMovementCells(World& world, TargetCell& target)
{
	bool foundWalkable = false;
	bool foundBlocker = false;

	for (auto i = 0; i < world.GetEntities().size(); i++)
	{
		// identificar si es una tile
		// quizas filtrar el array antes de iterar seria lo mas seguro
		GameEntity* tile = world.GetEntities()[i];
		int colPosition = target.gridPosition.y;
		int rowPosition = target.gridPosition.x; // DA -128 int al llegar a fila 15 col 8 ( 17 en el valor, el dato esta mal, se suma 2 veces en algunas iteraciones al presionar el boton)
		if (rowPosition == world.GetEntities()[i]->m_CellGrid.row && colPosition == world.GetEntities()[i]->m_CellGrid.col) // es una tile existente o caminable?
		{
			if (tile->m_Id == SPIRIT || tile->m_Id == WALL || tile->m_IsEntityPlanted) // faltaria validar al jugador
			{
				foundBlocker = true;
			} else if (tile->m_Id == GRASS1)
			{
				target.targetPosition = tile->m_Position;
				target.targetSize = tile->m_Size;
				target.targetCenter = tile->GetCenter(); // validar este calculo, que sea correcto
				target.targetIDSelf = tile->m_Id;
				target.isTarget = true;
				foundWalkable = true;
			}
		}
	}

	target.isTarget = foundWalkable && !foundBlocker;
}

// posible metodo para usar para plantar items en el mapa
void PlayerInputComponent::MoveGridPosition(GameEntity& entity, std::vector<GameEntity*> entities, int index)
{
	if (index > entities.size() - 1)
		return;

	glm::vec2 centerTile = entities[index]->GetCenter();
	g_tilePosition = index;
	entity.m_Position = centerTile - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f);
}

void PlayerInputComponent::PlantItem(World& world, GameEntityType type, GameEntity* target)
{
	world.PlantItemInWorld(type, target);
}

void PlayerInputComponent::RemoveItemFromGround(World& world, GameEntity* item)
{
	world.RemoveEntity(item);
}



