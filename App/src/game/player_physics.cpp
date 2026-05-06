#include "player_physics.h"

PlayerPhysicsComponent::PlayerPhysicsComponent()
{

}

void PlayerPhysicsComponent::Update(GameEntity& entity)
{
	if (entity.m_Position.x > m_LastPosition.x)
        m_IsWalkingRight = true;
    else {
        m_IsWalkingRight = false;
        m_IsIdle = true;
    }
}

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

