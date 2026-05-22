#include "game_entity_factory.h"
#include "player_input.h"
#include "player_physics.h"
#include "player_graphics.h"
#include "spirit_input.h"
#include "spirit_physics.h"
#include "spirit_graphics.h"

GameEntity* GameEntityFactory::CreatePlayer() // aca uso el "patron factory" para crear una entidad de jugador
{
    PlayerInputComponent* input = new PlayerInputComponent();
    PlayerPhysicsComponent* physics = new PlayerPhysicsComponent();
    PlayerGraphicsComponent* graphics = new PlayerGraphicsComponent(physics);

    return new GameEntity(input,
        physics,
        graphics);
}

GameEntity* GameEntityFactory::CreateEnemy() 
{
    SpiritInputComponent* input = new SpiritInputComponent();
    SpiritPhysicsComponent* physics = new SpiritPhysicsComponent();
    SpiritGraphicsComponent* graphics = new SpiritGraphicsComponent(physics);

    return new GameEntity(input,
        physics,
        graphics);
}