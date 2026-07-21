#include "game_entity_factory.h"
#include "player_input.h"
#include "player_physics.h"
#include "player_graphics.h"
#include "spirit_input.h"
#include "spirit_physics.h"
#include "spirit_graphics.h"
#include "item_input.h"
#include "item_graphics.h"

GameEntity* GameEntityFactory::CreatePlayer() // aca uso el "patron factory" para crear una entidad de jugador
{
    PlayerPhysicsComponent* physics = new PlayerPhysicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent(physics);
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

GameEntity* GameEntityFactory::CreateItem() 
{
    ItemPhysicsComponent* physics = new ItemPhysicsComponent();
    ItemInputComponent* input = new ItemInputComponent(physics);
    ItemGraphicsComponent* graphics = new ItemGraphicsComponent(physics);

    return new GameEntity(input,
        physics,
        graphics);
}