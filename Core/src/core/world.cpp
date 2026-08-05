#include "world.h"
#include "application.h"
#include "data/entities/entity.h"
#include "util.h"

#include <iostream>
#include <thread>
#include <chrono>

constexpr int INITIAL_X_POS = 8;
constexpr int INITIAL_Y_POS = 7;
constexpr int INITIAL_PLAYER_X_SIZE = 50;
constexpr int INITIAL_PLAYER_Y_SIZE = 50;
constexpr int INITIAL_ENEMY_X_SIZE = 60;
constexpr int INITIAL_ENEMY_Y_SIZE = 55;
constexpr int PLAYER_VELOCITY = 0;
constexpr int ROW_CENTER = 110;
constexpr int COL_CENTER = 75;
constexpr int WORLD_WIDTH = 800;
constexpr int WORLD_HEIGHT = 600;

constexpr int GRID_WIDTH = 13;
constexpr int GRID_HEIGHT = 15;


// constexpr int WORLD_WIDTH = 800 + ROW_CENTER; // el tamaño del ancho mas el centrado de la fila de la grilla 
// constexpr int WORLD_HEIGHT = 600 + COL_CENTER; // el tamaño del alto mas el centrado de la col de la grilla


World::World(IEntityFactory* factory)
	: m_EntityFactory(factory)

{
	glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	m_WorldBounds.bounds.x = 0.f;
	m_WorldBounds.bounds.y = 0.f;
	// m_WorldBounds.width = framebufferSize.x - 200; // posible side menu
	m_WorldBounds.width = framebufferSize.x;
	m_WorldBounds.height = framebufferSize.y;

	// inicializo 8x8 grid del mundo
	m_GameLevel = {
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,1,1,1,1,1,1,1,1,3,3,3},
		{3,3,3,1,3,3,1,1,3,3,1,3,3,3},
		{3,3,3,1,3,1,1,1,1,3,1,3,3,3},
		{3,3,3,1,3,1,1,1,1,3,1,3,3,3},
		{3,3,3,1,1,1,3,3,1,1,1,3,3,3},
		{3,3,3,1,3,1,3,3,1,3,1,3,3,3},
		{3,3,3,1,3,1,1,1,1,3,1,3,3,3},
		{3,3,3,1,3,3,1,1,3,3,1,3,3,3},
		{3,3,3,1,1,1,1,1,1,1,1,3,3,3},
		{3,3,3,1,1,1,1,1,1,1,1,3,3,3},
		{3,3,3,1,1,1,1,1,1,1,1,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3}
	};

	InitializeEntities();
}

World::~World()
{
}

void World::InitializeEntities()
{
	glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	m_TileMap = new Engine::TileManager(&m_GameLevel);
	m_Entities = m_TileMap->GenerateTileBoard(m_WorldBounds.width, m_WorldBounds.height);

	GameEntity* Player = m_EntityFactory->CreatePlayer();

	glm::vec2 playerPosition(INITIAL_X_POS, INITIAL_Y_POS);
	glm::vec2 playerSize(INITIAL_PLAYER_X_SIZE, INITIAL_PLAYER_Y_SIZE);
	glm::vec2 enemySize(INITIAL_ENEMY_X_SIZE, INITIAL_ENEMY_Y_SIZE);

	Player->m_Id = PLAYER;
	Player->m_Size = playerSize;
	Player->m_CellGrid.row = INITIAL_X_POS;
	Player->m_CellGrid.col = INITIAL_Y_POS;
	Player->m_Position = m_Entities[m_GameLevel.size() / 2]->GetCenter() - glm::vec2(
		Player->m_Size.x / 2.0f,
		Player->m_Size.y / 2.0f); // ubicar al jugador en el centro de la tile

	for (auto i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->m_CellGrid.row == INITIAL_X_POS
			&& m_Entities[i]->m_CellGrid.col == INITIAL_Y_POS)
		{
			Player->m_Position = m_Entities[i]->m_Position;
			break;
		}
	}

	Player->m_TileIndex = m_GameLevel.size() / 2;
	Player->m_Velocity = glm::vec2(PLAYER_VELOCITY);
	Player->m_Color = glm::vec3(1.0f);

	m_Entities.push_back(Player);

	GameEntity* TorchItem1 = m_EntityFactory->CreateItem();

	TorchItem1->m_Id = ITEM;
	TorchItem1->m_Color = glm::vec3(1.f);
	// TorchItem1->m_Position = plantTileObjective->m_Position;
	// TorchItem1->m_Size = plantTileObjective->m_Size;

	GameEntity* TorchItem2 = m_EntityFactory->CreateItem();

	TorchItem2->m_Id = ITEM;
	TorchItem2->m_Color = glm::vec3(1.f);
	// TorchItem2->m_Position = plantTileObjective->m_Position;
	// TorchItem2->m_Size = plantTileObjective->m_Size;

	GameEntity* TorchItem3 = m_EntityFactory->CreateItem();

	TorchItem3->m_Id = ITEM;
	TorchItem3->m_Color = glm::vec3(1.f);
	// TorchItem3->m_Position = plantTileObjective->m_Position;
	// TorchItem3->m_Size = plantTileObjective->m_Size;

	m_PlayerInventoryVector.push_back(TorchItem1);
	m_PlayerInventoryVector.push_back(TorchItem2);
	m_PlayerInventoryVector.push_back(TorchItem3);

	m_PlayerInventorySlots = m_PlayerInventoryVector.size();

	std::vector<glm::ivec2> enemyCellPositions = {
		glm::vec2(5, 3),
		glm::vec2(7, 3),
		glm::vec2(5, 9),
		glm::vec2(7, 10),
		glm::vec2(6, 10),
		glm::vec2(7, 10),
	};

	std::vector<glm::ivec2> enemyVectorPositions;

	for (int i = 0; i < enemyCellPositions.size(); ++i)
	{
		for (int j = 0; j < m_Entities.size(); ++j)
		{
			if (m_Entities[j]->m_Id == GRASS1 && m_Entities[j]->m_CellGrid.row == enemyCellPositions[i].x &&
				m_Entities[j]->m_CellGrid.col == enemyCellPositions[i].y)
			{
				m_Entities[j]->m_IsTileNotPlantable = true;
				enemyVectorPositions.push_back(m_Entities[j]->m_Position);
				break;
			}
		}
	}

	const int spiritsSize = enemyVectorPositions.size();

	for (auto i = 0; i < spiritsSize; ++i)
	{
		GameEntity* Spirit = m_EntityFactory->CreateEnemy();

		Spirit->m_Id = SPIRIT;
		Spirit->m_Position = enemyVectorPositions[i];
		// Spirit->m_Size = playerSize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Size = enemySize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Velocity = glm::vec2(PLAYER_VELOCITY); // misma velocidad que el jugador
		Spirit->m_Color = glm::vec3(1.0f); // a definir, podria cambiar el color de una textura de espiritu
		Spirit->m_CellGrid.row = enemyCellPositions[i].x;
		Spirit->m_CellGrid.col = enemyCellPositions[i].y;
		AddEntity(Spirit);
	}
}

void World::Update()
{
	// std::cout << "updating world!" << std::endl;
	if (m_Entities.size() == 0)
		return;

	for (auto i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->m_Id == ITEM)
		{
			// if (m_Entities[i]->m_IsItemPlanted)
			// {
			// 	std::cout << "vela plantada, tiempo para que se apague de 5 segundos..\n";
			// 	std::this_thread::sleep_for(std::chrono::seconds(5));
			// 	std::cout << "vela apagada\n";
			// 	RemoveEntity(m_Entities[i]);
			// }

			if (m_Entities[i]->m_IsItemPlanted)
			{
				auto start = std::chrono::steady_clock::now();
				auto duration = std::chrono::seconds(5);

				while (std::chrono::steady_clock::now() - start < duration)
				{
					std::cout << "vela plantada, tiempo para que se apague de 5 segundos..\n";
				}
				std::cout << "vela apagada\n";

				RemoveEntity(m_Entities[i]);
			}
		}
	}
}

void World::PlantItemInWorld(unsigned int type, GameEntity* plantTileObjective)
{
	// // crear entidad con la data del item
	if (m_PlayerInventoryVector.size() == 0)
		return;
	// agrega el primer item del inventario al mundo, luego  elimina del inventario (no el puntero)
	m_PlayerInventoryVector[0]->m_Position = plantTileObjective->m_Position;
	m_PlayerInventoryVector[0]->m_Size = plantTileObjective->m_Size;
	m_PlayerInventoryVector[0]->m_IsItemPlanted = true;

	AddEntity(m_PlayerInventoryVector[0]);

	m_PlayerInventoryVector.erase(m_PlayerInventoryVector.begin() + 0);

	plantTileObjective->m_IsTileNotPlantable = true; // esto provoca bugs al eliminar enemigos o eliminar items
}


void World::RenderWorld()
{
}

void World::AddEntity(GameEntity* entity)
{
	if (entity == nullptr)
		return;

	m_Entities.push_back(entity);
}

void World::AddItemToPlayerInventory(GameEntity* item)
{
	if (item == nullptr)
		return;

	m_PlayerInventoryVector.push_back(item);
}

void World::RemoveEntity(GameEntity* entity)
{
	if (entity == nullptr)
		return;

	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);

	if (it != m_Entities.end())
	{
		delete *it;
		m_Entities.erase(it);
	}
}


