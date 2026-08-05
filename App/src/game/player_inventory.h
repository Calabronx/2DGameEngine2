#pragma once
#ifndef PLAYER_INVENTORY 
#define PLAYER_INVENTORY

#include <vector>
#include <core/data/entities/entity.h>
#include <core/data/entities/ientity_factory.h>

class PlayerInventory
{
    public:
    	PlayerInventory(IEntityFactory* entityFactory);
    	~PlayerInventory();

    	void AddItem(GameEntity* item);

        //
        

    private:
    	IEntityFactory				   *m_EntityFactory;
};

#endif 
