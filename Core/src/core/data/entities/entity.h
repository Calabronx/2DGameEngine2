#pragma once
#ifndef GAME_ENTITY
#define GAME_ENTITY

#include <glm/glm.hpp>
#include <cstdint>
#include "../../input/input_component.h"
#include "../../physics.h"
#include "../../renderer/graphics.h"

class GameEntity
{
	public:
								GameEntity();
								GameEntity(InputComponent* input, PhysicsComponent* physics ,GraphicsComponent *graphics);
		// virtual 				~GameEntity() {}

		// void 					Update(World& world, Graphics& graphics);
		void 					Update(Renderer::SpriteRenderer& renderer);

		bool 					IsDestroyed() { return m_Destroyed; };

		InputComponent* 		GetInput() { return m_Input; };
		PhysicsComponent* 		GetPhysics() { return m_Physics; };
		GraphicsComponent* 		GetGraphics() { return m_Graphics; };

	public:
		uint32_t	m_Id = 0;

		glm::vec2 	m_Position;
		glm::vec2 	m_Velocity;
		glm::vec2 	m_Size;
		glm::vec3 	m_Color;
		float 		m_Rotation;
	private:
		bool m_Destroyed;

		InputComponent 		*m_Input;
		PhysicsComponent	*m_Physics;
		GraphicsComponent 	*m_Graphics;
};

#endif


