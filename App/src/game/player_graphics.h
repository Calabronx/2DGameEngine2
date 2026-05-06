#pragma once

#include "core/renderer/graphics.h"
#include "player_physics.h"

class PlayerGraphicsComponent : public GraphicsComponent
{
	public:
						PlayerGraphicsComponent(PlayerPhysicsComponent* physics);


		void 			Update(GameEntity& entity, Renderer::SpriteRenderer& renderer);

		void 		 	MovePlayer(GameEntity& entity, glm::vec2 position);

	private:
		PlayerPhysicsComponent* m_PlayerPhysics;

		Renderer::Sprite 		m_SpriteIdle;
		Renderer::Sprite 		m_SpriteWalkLeft;
		Renderer::Sprite 		m_SpriteWalkRight;
		Renderer::Sprite 		m_SpriteWalkUp;
		Renderer::Sprite 		m_SpriteWalkDown;
};

