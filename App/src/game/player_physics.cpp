#include "player_physics.h"
#include <iostream>

PlayerPhysicsComponent::PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::Update(GameEntity& entity)
{
    if (entity.m_Velocity.x < 0)
    {
        // std::cout << "IS WALKING LEFT" << std::endl;
        m_IsWalkingLeft = true;
        m_IsWalkingRight = false;
        m_IsWalkingDown = false;
        m_IsWalkingUp = false;
        m_IsIdle = false;
    }

    if (entity.m_Velocity.x > 0)
    {
        // std::cout << "IS WALKING RIGHT" << std::endl;
        m_IsWalkingRight = true;
        m_IsWalkingLeft = false;
        m_IsWalkingDown = false;
        m_IsWalkingUp = false;
        m_IsIdle = false;
    }

    if (entity.m_Velocity.y > 0)
    {
        // std::cout << "IS WALKING DOWN" << std::endl;
        m_IsWalkingDown = true;
        m_IsWalkingRight = false;
        m_IsWalkingLeft = false;
        m_IsWalkingUp = false;
        m_IsIdle = false;
    }

    if (entity.m_Velocity.y < 0)
    {
        // std::cout << "IS WALKING UP" << std::endl;
        m_IsWalkingUp = true;
        m_IsWalkingRight = false;
        m_IsWalkingLeft = false;
        m_IsWalkingDown = false;
        m_IsIdle = false;
    }

    if (entity.m_Velocity.x == 0 && entity.m_Velocity.y == 0)
    {
        // std::cout << "IS STAND" << std::endl;
        m_IsIdle = true;
        m_IsWalkingUp = false;
        m_IsWalkingRight = false;
        m_IsWalkingLeft = false;
        m_IsWalkingDown = false;
    }

    if(entity.m_Position.x == m_LastPosition.x)
    { 
    }

    entity.m_Position.x +=  entity.m_Velocity.x;
    entity.m_Position.y +=  entity.m_Velocity.y;
    m_LastPosition = entity.m_Position;

    // std::cout << "X: " << entity.m_Position.x << " Y: " << entity.m_Position.y << " " << std::endl;
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
    return m_IsWalkingLeft;
}

bool PlayerPhysicsComponent::IsWalkingUpDirection() const
{   
    return m_IsWalkingUp;
}

bool PlayerPhysicsComponent::IsWalkingDownDirection() const
{
    return m_IsWalkingDown;
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

