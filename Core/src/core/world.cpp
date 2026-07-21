#include "world.h"
#include "application.h"
#include "data/entities/entity.h"
#include "util.h"

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
	glm::vec2 playerSize(INITIAL_PLAYER_X_SIZE,INITIAL_PLAYER_Y_SIZE);
	glm::vec2 enemySize(INITIAL_ENEMY_X_SIZE,INITIAL_ENEMY_Y_SIZE);

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

	GameEntity* TorchItem = m_EntityFactory->CreateItem();
	TorchItem->m_Id = ITEM;
	TorchItem->m_Color = glm::vec3(1.f);

	m_Entities.push_back(TorchItem);

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
		m_Entities.push_back(Spirit);
	}
}

void World::CreateItemEntity(unsigned int type, GameEntity* plantTileObjective)
{
	GameEntity* TorchItem = m_EntityFactory->CreateItem();

	TorchItem->m_Id = type;
	TorchItem->m_Color = glm::vec3(1.f);
	TorchItem->m_Position = plantTileObjective->m_Position;
	TorchItem->m_Size = plantTileObjective->m_Size;
	AddEntity(TorchItem);

	m_PlayerInventoryVector.push_back(TorchItem);
}

void World::AddEntity(GameEntity* entity)
{
	if (m_Entities == nullptr || entity == nullptr)
		return;

	m_Entities.push_back(entity);
}
