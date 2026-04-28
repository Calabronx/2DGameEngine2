#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <core/game_object.h>

namespace Application
{
	class Player : public GameObject
	{
		public:
						Player	(glm::vec2 pos,
								 glm::vec2 size, 
								 Renderer::Texture sprite,
								 glm::vec3 color,
								 glm::vec2 velocity);

			void 				Move(glm::vec2 position);

		private:
			int m_PlayerHealth;
	};
}
#endif

