#include "spirit_input.h"
#include <core/input/input.h>
#include <Core/application.h>
#include <iostream>
#include <cassert>
#include <random>

namespace
{
	int g_tilePosition = 0;
	int g_plantedCount = 0;
	int g_tilesCollisionIndex = 0;
	int g_DirectionsBlocked = 0;

	bool g_IsMoving = false;
	bool g_Arrived = false;
	bool g_ChangeDirection = false;

	float g_ControlledVelocity = 0.60f;
	Target g_Target;
};

SpiritInputComponent::SpiritInputComponent()
{
	// primer solucion a iniciar el camino de el componente de IA
	// para que direcion se mueve el fantasma
	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> distrib(1,5); // entre 6 numeros random, se mueve a la direccion que toque
	// no me convence de igual manera cuanto cuesta o que hace esto... 

	int random_num = distrib(gen);

	// switch (random_num)
	// {
	// 	case 1:
	// 	 	m_Direction = DOWN;
	// 	 	break;
	// 	case 2:
	// 	case 3:
	// 	 	m_Direction = UP;
	// 	 	break;
	// 	case 4:
	// 	 	m_Direction = RIGHT;
	// 	 	break;
	// 	case 5:
	// 	 	m_Direction = LEFT;
	// 	 	break;
	// }
	m_Direction = RIGHT;
}
void SpiritInputComponent::Update(GameEntity& entity, World& world, float ts)
{
	if (Input::IsMousePressed())
	{
		if(entity.IsSelected(Input::GetCursorPosition()))
		{
		   // std::cout<< "Enemigo Fila :" << entity.m_CellGrid.row << " Columna : " <<  entity.m_CellGrid.col << std::endl;
			// if (entity.m_Tile != nullptr)
			entity.m_Tile->m_IsEntityPlanted = false;
			assert(entity.m_Tile != nullptr);
			world.RemoveEntity(&entity);
		}
	}

	PatrolIA(world, entity, m_Direction, ts);
}

void SpiritInputComponent::PatrolIA(World &world, GameEntity& entity, Direction& direction, float ts)
{
	Target targetTemp = {};
	targetTemp.gridPosition = { entity.m_CellGrid.row, entity.m_CellGrid.col };

	if (direction == DOWN)
	{
		targetTemp.gridPosition.y += 1;
	} else if (direction == UP)
	{
		targetTemp.gridPosition.y -= 1;
	} else if (direction == LEFT)
	{
		targetTemp.gridPosition.x -= 1;
	} else if (direction == RIGHT)
	{
		targetTemp.gridPosition.x += 1;
	}

	if (g_Target.gridPosition.y >= world.GetWorldLimits().col)
		return;

	GetMovementCells(world, targetTemp);

	/**
	 * Definir como validar un rango de validaciones al dirigir a una posicion,
	 * actualmente si se dirige a la derecha y cambia de sentido al llegar a una pared, se mueve a la izquerda
	 * BUG - Lo que pasa que si la entidad tiene una pared una posicion a la derecha y otra a la izquierda se bloquea, 
	 * tiene que validar este caso y cambiar de sentido a por ej: arriba y abajo
	 * si en el sentido que va, esta bloqueado en ambas direcciones, cambiar de sentido ("girar")
	 * 
	 **/ 


	if (!targetTemp.isTarget)
	{
		if (g_DirectionsBlocked == 2)
		{
			if (direction == LEFT || direction == RIGHT)
			{
				m_Direction = UP;
				g_DirectionsBlocked = 0;
			} else if (direction == UP || direction == DOWN)
			{
				m_Direction = LEFT;
				g_DirectionsBlocked = 0;
			}
		}

		// no seas paja... cambia esto que es feo
		// definir un componente que maneje la logica del control de IA, para poder usarlo
		if (direction == DOWN)
		{
			m_Direction = UP;
		} else if (direction == UP)
		{
			m_Direction = DOWN;
		} else if (direction == LEFT)
		{
			m_Direction = RIGHT;
		} else if (direction == RIGHT)
		{
			m_Direction = LEFT;
		}
		return;
	}

	g_IsMoving = true;
	g_Target = targetTemp;

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
			g_Target.isTarget = false;
			g_Arrived = false;

			return;
		}

		glm::vec2 direction = toTarget / distance;

		entity.m_Velocity.x = direction.x * WALK_ACCELERATION * ts * 0.60f;
		entity.m_Velocity.y = direction.y * WALK_ACCELERATION * ts * 0.60f;
	}
}

void SpiritInputComponent::ValidateMovement(World& world, Target& target, GameEntity& tile)
{

}
void SpiritInputComponent::GetMovementCells(World& world, Target& target) // cambiar el nombre del metodo..
{
	bool foundWalkable = false;
	bool foundBlocker = false;

	// tengo que definir que este metodo obtenga la tile por parametro a la que valida, y ejecutar el for en la world class
	// asi todos los enemigos entidades del juego validan en un solo for loop
	// en lugar que todos ejecuten un for loop cada uno
	// 100 entidades enemigos = 100 for loops que iteran la lista de entidades del mundo
	// resultado, vuelve lentisimo el juego, uso de ram innecesaria // En release funciona rapido, pero hay que pensar otra manera quizas
	for (auto i = 0; i < world.GetEntities().size(); i++)
	{
		// identificar si es una tile
		// quizas filtrar el array antes de iterar seria lo mas seguro
		GameEntity* tile = world.GetEntities()[i];
		int colPosition = target.gridPosition.y;
		int rowPosition = target.gridPosition.x; 
		if (rowPosition == world.GetEntities()[i]->m_CellGrid.row && colPosition == world.GetEntities()[i]->m_CellGrid.col) // es una tile existente o caminable?
		{
			if (tile->m_Id == SPIRIT || tile->m_Id == WALL || tile->m_IsEntityPlanted) // faltaria validar al jugador
			{
				foundBlocker = true;
			}
			else if (tile->m_Id == GRASS1)
			{
				target.targetPosition = tile->m_Position;
				target.targetSize = tile->m_Size;
				target.targetCenter = tile->GetCenter(); // validar este calculo, que sea correcto
				target.targetIDSelf = tile->m_Id;
				target.isTarget = true;
				foundWalkable = true;
				g_DirectionsBlocked = 0;
			}
		}
	}

	target.isTarget = foundWalkable && !foundBlocker;

	if (!target.isTarget)
	{
		++g_DirectionsBlocked;
	}
}


