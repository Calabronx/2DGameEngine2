#include "player_physics.h"
#include <iostream>

PlayerPhysicsComponent::PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::Update(GameEntity& entity)
{
	// if (entity.m_Position.x > m_LastPosition.x)
    //     MovePlayer(entity, )
    //     m_IsWalkingRight = true;
    // else {
    //     m_IsWalkingRight = false;
    //     m_IsIdle = true;
    // }
    if (entity.m_Velocity.x < 0)
    {
        std::cout << "IS WALKING LEFT" << std::endl;
    }

    if (entity.m_Velocity.x > 0)
    {
        std::cout << "IS WALKING RIGHT" << std::endl;
        m_IsWalkingRight = true;
    }

    if (entity.m_Velocity.y < 0)
    {
        std::cout << "IS WALKING UP" << std::endl;
    }

    if (entity.m_Velocity.y > 0)
    {
        std::cout << "IS WALKING DOWN" << std::endl;
    }

    entity.m_Position.x += entity.m_Velocity.x;
    entity.m_Position.y += entity.m_Velocity.y;
    std::cout << "X: " << entity.m_Position.x << " Y: " << entity.m_Position.y << " " << std::endl;
    // resolver colision con el mundo (coordenadas jugador)

}

// void PlayerPhysicsComponent::MovePlayer(GameEntity& entity, glm::vec2 position)
// {
//     entity.m_Position.x += position.x * entity.m_Velocity.x;
//     entity.m_Position.y += position.y * entity.m_Velocity.y;

//     std::cout << "X: " << entity.m_Position.x << " Y: " << entity.m_Position.y << " " << std::endl;
// }

bool PlayerPhysicsComponent::IsWalkingRightDirection() const
{
    return m_IsWalkingRight;
}

bool PlayerPhysicsComponent::IsWalkingLeftDirection() const
{
    return false;
}

bool PlayerPhysicsComponent::IsWalkingUpDirection() const
{   
    return false;
}

bool PlayerPhysicsComponent::IsWalkingDownDirection() const
{
    return false;
}

bool PlayerPhysicsComponent::IsIdle() const
{
    return m_IsIdle;
}

bool PlayerPhysicsComponent::IsTakingDamage() const
{
    return false;
}

bool PlayerPhysicsComponent::IsCollision(GameEntity& entity1, GameEntity& entity2) const
{
    return false;
}

