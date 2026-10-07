#pragma once
#ifndef SPIRIT_INPUT_H
#define SPIRIT_INPUT_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include <core/world.h>

struct Target
{
    glm::vec2 targetPosition;
    glm::vec2 targetSize;
    glm::vec2 targetCenter;
    glm::ivec2 gridPosition;
    bool isTarget = false;
    uint32_t targetIDSelf;
};

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class SpiritInputComponent : public InputComponent
{
    public:
        SpiritInputComponent();
        void Update(GameEntity& entity, World& world, float ts);
        void ValidateMovement(World& world, Target& target, GameEntity& tile);
    private:
        void GetMovementCells(World& world, Target& target);
        void PatrolIA(World& world, GameEntity& entity, Direction& direction, float ts);

        static const int WALK_ACCELERATION = 2;

        Direction m_Direction;

};
#endif 

