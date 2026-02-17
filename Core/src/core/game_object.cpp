#include "game_object.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Renderer::Texture sprite, glm::vec3 color)
	: m_Position(pos)
	, m_Size(size)
	, m_Velocity()
	, m_Color(color)
	, m_Rotation(0.0f)
	, m_Sprite(sprite)
	, m_Destroyed(false)
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Renderer::Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: m_Position(pos)
	, m_Size(size)
	, m_Velocity(velocity)
	, m_Color(color)
	, m_Rotation(0.0f)
	, m_Sprite(sprite)
	, m_Destroyed(false)
{
}

GameObject::GameObject()
{
}



void GameObject::RenderObject(Renderer::SpriteRenderer& renderer)
{
	renderer.RenderSprite(m_Sprite, m_Position, m_Size, m_Rotation, m_Color);
}
