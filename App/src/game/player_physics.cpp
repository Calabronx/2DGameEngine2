#include "player_physics.h"
#include <iostream>

PlayerPhysicsComponent::PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::Update(GameEntity& entity, World& world)
{

    glm::vec2 worldLimit = world.GetWorldLimits().bounds;
    /*if (entity.m_Position.x > worldLimit.x)
    {
        std::cout << "SALIO DEL MAPA A LA DERECHA DEL MUNDO" << std::endl;
    } else if (entity.m_Position.x < worldLimit.x)
    {
        std::cout << "SALIO DEL MAPA A LA IZQ DEL MUNDO" << std::endl;
    } else if (entity.m_Position.y > worldLimit.y)
    {
        std::cout << "SALIO DEL MAPA ARRIBA DEL MUNDO" << std::endl;
    } else if (entity.m_Position.y < worldLimit.y)
    {
        std::cout << "SALIO DEL MAPA ABAJO DEL MUNDO" << std::endl;
    }*/

    //if (entity.m_Position.x > )


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

    /**
     * detectar el centro de la tile en donde estoy parado
     **/ 

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
    float x = entity1.m_Position.x;
    float y = entity1.m_Position.y;
    int w = entity1.m_Size.x;
    int h = entity1.m_Size.y;

    bool collision = ((entity2.m_Position.x >= x) && (entity2.m_Position.x <= x + w))
    && ((entity2.m_Position.y >= y) && (entity2.m_Position.y <= y + h));

    return collision;
}

bool PlayerPhysicsComponent::IsCollision(glm::vec2 position1, glm::vec2 size1, glm::vec2 position2,glm::vec2 size2) const
{
    float x = position1.x;
    float y = position1.y;
    int w = size1.x;
    int h = size1.y;

    bool collision = ((position2.x >= x) && (position2.x <= x + w))
    && ((position2.y >= y) && (position2.y <= y + h));

    return collision;
}