#pragma once
#ifndef GAME_ENTITY
#define GAME_ENTITY

#include <glm/glm.hpp>
#include <cstdint>
#include "../../input/input_component.h"
#include "../../physics.h"
#include "../../renderer/graphics.h"
#include <string>

#include <chrono>

enum GameEntityType
{
	PLAYER,
	SPIRIT,
	GRASS1,
	GRASS2,
	WALL,
	ITEM
};

struct Cell
{
	int row, col;
};

class GameEntity
{
	public:
								GameEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent *graphics);
		 						~GameEntity() {}

		bool 					IsDestroyed() { return m_Destroyed; };
		bool					IsSelected(glm::vec2 mousePos);

		glm::vec2				GetCenter() const;

		InputComponent* 		GetInput() { return m_Input; };
		PhysicsComponent* 		GetPhysics() { return m_Physics; };
		GraphicsComponent* 		GetGraphics() { return m_Graphics; };

	public:
		uint32_t	m_Id = 0;
		int 		m_TileIndex;
		Cell		m_CellGrid;
		glm::vec2 	m_Position;
		glm::vec2 	m_Velocity;
		glm::vec2 	m_Size;
		glm::vec3 	m_Color;
		float 		m_Rotation;
		bool 		m_IsTileNotPlantable;
		std::chrono::steady_clock::time_point m_PlantedTime;
		bool 			m_IsEntityPlanted;
		bool 			m_TimerStarted;
		std::string		m_EntityName; // capaz podria ser una descripcion de la entidad

		GameEntity			*m_Tile;
	private:
		bool m_Destroyed;


		InputComponent 		*m_Input;
		PhysicsComponent	*m_Physics;
		GraphicsComponent 	*m_Graphics;
};

#endif


