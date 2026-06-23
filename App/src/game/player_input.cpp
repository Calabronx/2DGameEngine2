#include "player_input.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <core/input/input.h>
#include <core/application.h>
#include "core/world.h"
#include <core/util.h>

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

	struct TargetCell
	{
		glm::vec2 targetPosition;
		glm::vec2 targetSize;
		glm::vec2 targetCenter;
		glm::ivec2 gridPosition;
		bool isTarget = false;
		uint32_t targetIDSelf;
		uint32_t targetW_ID;
		uint32_t targetS_ID;
		uint32_t targetD_ID;
		uint32_t targetA_ID;
	};

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
	entity.m_Velocity.x = 0;
	entity.m_Velocity.y = 0;

	std::vector<std::vector<uint32_t>> gridLevel = world.GetGridLevel();
	const float deltaTime = Engine::Application::GetDeltaTime();

	if (!g_IsMoving)
	{
		if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
			if (g_Target.targetIDSelf == WALL) // tiene que validar la que tiene arriba
			{
				return;
			}

			if (g_Target.gridPosition.y <= 0)
			{
				return;
			}
			g_IsMoving = true;
			g_Up = true;
			g_Target.gridPosition.y -= 1;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_D))
		{
			if (g_Target.gridPosition.x >= 13)
			{
				return;
			}
			g_IsMoving = true;
			g_Right = true;
			g_Target.gridPosition.x += 1;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_A))
		{
			if (g_Target.gridPosition.x <= 0)
			{
				return;
			}
			g_IsMoving = true;
			g_Left = true;
			g_Target.gridPosition.x -= 1;
		}
		else if (Input::IsKeyPressed(SDL_SCANCODE_S))
		{
			if (g_Target.gridPosition.y >= 15)
			{
				return;
			}
			g_IsMoving = true;
			g_Down = true;
			g_Target.gridPosition.y += 1;
		}
		std::cout << "GRID ROW: "<<  g_Target.gridPosition.x << std::endl;
		std::cout << "GRID COL: "<<  g_Target.gridPosition.y << std::endl;
	}

	if (g_IsMoving && !g_Target.isTarget)
	{
		for (auto i = 0; i < world.GetEntities().size(); i++)
		{
			// identificar si es una tile
			// quizas filtrar el array antes de iterar seria lo mas seguro
			/*if (world.GetEntities()[i]->m_Id != GRASS1 || world.GetEntities()[i]->m_Id != GRASS2)
			{
				break;
			}*/
			GameEntity* tile = world.GetEntities()[i];
			int colPosition = g_Target.gridPosition.y;
			int rowPosition = g_Target.gridPosition.x; // DA -128 int al llegar a fila 15 col 8 ( 17 en el valor, el dato esta mal, se suma 2 veces en algunas iteraciones al presionar el boton)
			if (rowPosition == world.GetEntities()[i]->m_CellGrid.row
				&& colPosition == world.GetEntities()[i]->m_CellGrid.col) // es una tile existente o caminable?
			{
				g_Target.targetPosition = tile->m_Position;
				g_Target.targetSize = tile->m_Size;
				g_Target.targetCenter = tile->GetCenter(); // validar este calculo, que sea correcto
				g_Target.targetIDSelf = tile->m_Id;
				g_Target.isTarget = true;
				break;
			}
		}
	}

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
		{
			return;
		}
		// entity.m_Velocity.y += WALK_ACCELERATION * deltaTime;
		// std::cout << "mouse moved or pressed "<< std::endl;
		glm::vec2 cursorPos = Input::GetCursorPosition();
		std::cout << "mouse x: " << cursorPos.x << " mouse y: " << cursorPos.y << std::endl;
		bool clicked = false;
		for (auto i = 0; i < world.GetEntities().size() && !g_firstClick; i++)
		{
			if (world.GetEntities()[i]->IsSelected(cursorPos)) // movimento del jugador en las tiles, deberia identificar si es una Tile real
			{
				std::cout << "tile id position : " << i << std::endl;
				// glm::vec2 objective = world.GetEntities()[i]->GetCenter();
				// entity.m_Position = objective - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f); // ubicar al jugador en el centro de la tile
				if (g_tilePosition - 8 == i)
				{
					MoveGridPosition(entity, world.GetEntities(), g_tilePosition - 8);
				}
				else if (g_tilePosition + 8 == i)
				{
					MoveGridPosition(entity, world.GetEntities(), g_tilePosition + 8);
				}
				else if (g_tilePosition + 1 == i)
				{
					MoveGridPosition(entity, world.GetEntities(), g_tilePosition + 1);
				}
				else if (g_tilePosition - 1 == i)
				{
					MoveGridPosition(entity, world.GetEntities(), g_tilePosition - 1);
				}

				g_firstClick = true;
				// std::cout << "jugador toco la entidad: " << world.GetEntities()[i]->m_Id << std::endl;
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

void PlayerInputComponent::MoveGridPosition(GameEntity& entity, std::vector<GameEntity*> entities, int index)
{
	if (index > entities.size() - 1)
		return;

	glm::vec2 centerTile = entities[index]->GetCenter();
	g_tilePosition = index;
	entity.m_Position = centerTile - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f);
}

