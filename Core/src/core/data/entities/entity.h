#pragma once
#ifndef GAME_ENTITY
#define GAME_ENTITY

#include <glm/glm.hpp>
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

	public:
		glm::vec2 m_Position;
		glm::vec2 m_Velocity;
		glm::vec2 m_Size;
		glm::vec3 m_Color;
		float m_Rotation;
	private:
		bool m_Destroyed;

		InputComponent 		*m_Input;
		GraphicsComponent 	*m_Graphics;
		PhysicsComponent	*m_Physics;
};

#endif


