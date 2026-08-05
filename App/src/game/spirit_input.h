#pragma once
#ifndef SPIRIT_INPUT_H
#define SPIRIT_INPUT_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include <core/world.h>

class SpiritInputComponent : public InputComponent
{
    public:
        void Update(GameEntity& entity, World& world);

};
#endif 

