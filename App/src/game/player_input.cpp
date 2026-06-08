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

	struct TargetCell
	{
		glm::vec2 targetPosition;
		glm::vec2 targetSize;
		glm::ivec2 gridPosition;
	};

	TargetCell g_Target;

};

PlayerInputComponent::PlayerInputComponent(PlayerPhysicsComponent* physics)
	: m_PlayerPhysics(physics)
{
}

void PlayerInputComponent::Update(GameEntity& entity, World& world)
{
	entity.m_Velocity.x = 0;
	entity.m_Velocity.y = 0;

	g_Target.gridPosition.x = entity.m_CellGrid.row;
	g_Target.gridPosition.y = entity.m_CellGrid.col;

	const float deltaTime = Engine::Application::GetDeltaTime();

	if (!g_Down && !g_Right && !g_Left && Input::IsKeyPressed(SDL_SCANCODE_W))
	{
		g_IsMoving = true;
		g_Up = true;
		g_Target.gridPosition.y -= 1;

	}
	else if (!g_Down && !g_Left && !g_Up && Input::IsKeyPressed(SDL_SCANCODE_D))
	{
		g_IsMoving = true;
		g_Right = true;
		g_Target.gridPosition.x += 1;
	}
	else if (!g_Down && !g_Up && !g_Right && Input::IsKeyPressed(SDL_SCANCODE_A))
	{
		g_IsMoving = true;
		g_Left = true;
		g_Target.gridPosition.x -= 1;
	}
	else if (!g_Up && !g_Right && !g_Left && Input::IsKeyPressed(SDL_SCANCODE_S))
	{
		g_IsMoving = true;
		g_Down = true;
		g_Target.gridPosition.y += 1;
	}

	for (auto i = 0; i < world.GetEntities().size(); i++)
	{
		GameEntity* tile = world.GetEntities()[i];
		int colPosition = entity.m_CellGrid.col;
		int rowPosition = entity.m_CellGrid.row;
		if (rowPosition == world.GetEntities()[i]->m_CellGrid.row
			&& colPosition == world.GetEntities()[i]->m_CellGrid.col)
		{
			g_Target.targetPosition = tile->m_Position;
			g_Target.targetSize = tile->m_Size;
			break;
		}
	}

	if (g_IsMoving)
	{
		if (m_PlayerPhysics->IsCollision(entity.m_Position, entity.m_Size, g_Target.targetPosition, g_Target.targetSize))
		{
			g_IsMoving = false;
			entity.m_CellGrid.col = g_Target.gridPosition.y;
			entity.m_CellGrid.row = g_Target.gridPosition.x;
			g_Up = false;
			g_Down = false;
			g_Right = false;
			return;
		}

		if (g_Up)
		{
			entity.m_Velocity.y -= WALK_ACCELERATION * deltaTime;

		}
		else if (g_Down)
		{
			entity.m_Velocity.y += WALK_ACCELERATION * deltaTime;
		} else if (g_Right)
		{
			entity.m_Velocity.x += WALK_ACCELERATION * deltaTime;
		} else if (g_Left)
		{
			entity.m_Velocity.x -= WALK_ACCELERATION * deltaTime;
		}
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

