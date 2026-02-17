#pragma once
#ifndef GAME_OBJECT
#define GAME_OBJECT

/**
 * clase para poder represtar game objects del juego y comportamiento
 * 
 * definir atributos
 * 2d vectores
 * posicion
 * velocidad
 * color
 * 
 * definir metodo para renderizar utilizando el renderer como parametro
**/

#include <glm/glm.hpp>
#include "renderer/renderer.h"
#include "renderer/sprite_renderer.h"

class GameObject
{
	public:
		GameObject();
		GameObject(glm::vec2 pos, glm::vec2 size, Renderer::Texture sprite, glm::vec3 color, glm::vec2 velocity);
		GameObject(glm::vec2 pos, glm::vec2 size, Renderer::Texture sprite, glm::vec3 color);


		bool IsDestroyed() { return m_Destroyed; };

		virtual void RenderObject(Renderer::SpriteRenderer& renderer);

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Velocity;
		glm::vec2 m_Size;
		glm::vec3 m_Color;

		float m_Rotation;

		bool m_Destroyed;
		Renderer::Texture 	m_Sprite;

};
#endif

