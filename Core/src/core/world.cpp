#include "world.h"
#include "application.h"
#include "data/entities/entity.h"

constexpr int INITIAL_X_POS = 375;
constexpr int INITIAL_Y_POS = 275;
constexpr int INITIAL_PLAYER_X_SIZE = 80;
constexpr int INITIAL_PLAYER_Y_SIZE = 55;
constexpr int INITIAL_ENEMY_X_SIZE = 60;
constexpr int INITIAL_ENEMY_Y_SIZE = 55;
constexpr int PLAYER_VELOCITY = 0;

World::World(IEntityFactory* factory)
	: m_EntityFactory(factory)
{
	// inicializo 8x8 grid del mundo

	m_GameGrid = {
		{1,1,1,1,1,1,1,1},
		{2,2,2,1,1,2,2,1},
		{2,2,1,1,1,1,2,1},
		{2,2,1,1,1,1,2,1},
		{2,2,1,1,1,1,2,1},
		{2,2,4,4,4,3,2,1},
		{2,2,5,5,5,5,5,1},
		{2,2,2,2,2,2,2,1}
	};
	
	InitializeEntities();
}

World::~World()
{
}

void World::InitializeEntities()
{
	glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();

	m_TileMap = new Engine::TileManager(&m_GameGrid);
	m_TileMap->GenerateTileBoard(m_Entities, framebufferSize.x, framebufferSize.y);

	GameEntity* Player = m_EntityFactory->CreatePlayer();

	glm::vec2 playerPosition(INITIAL_X_POS, INITIAL_Y_POS);
	glm::vec2 playerSize(INITIAL_PLAYER_X_SIZE,INITIAL_PLAYER_Y_SIZE);
	glm::vec2 enemySize(INITIAL_ENEMY_X_SIZE,INITIAL_ENEMY_Y_SIZE);

	Player->m_Id = PLAYER;

	Player->m_Size = playerSize;
	Player->m_Position = m_Entities[27]->GetCenter() - glm::vec2(
													Player->m_Size.x / 2.0f,
													Player->m_Size.y / 2.0f); // ubicar al jugador en el centro de la tile
	Player->m_Velocity = glm::vec2(PLAYER_VELOCITY);
	Player->m_Color = glm::vec3(1.0f);

	m_Entities.push_back(Player);

	std::vector<glm::vec2> enemyPositions = {
		glm::vec2(22.382f, 29.1355f),
		glm::vec2(339.393f, 13.6976f),
		glm::vec2(708.326, 13.6976f),
		glm::vec2(708.326, 309.459f),
		glm::vec2(721.443f, 547.423f),
		glm::vec2(326.427f, 547.423f),
		glm::vec2(28.486f, 547.423f),
	};
	const int spiritsSize = enemyPositions.size();

	for (auto i = 0; i < spiritsSize; ++i)
	{
		GameEntity* Spirit = m_EntityFactory->CreateEnemy();

		Spirit->m_Id = SPIRIT;
		Spirit->m_Position = enemyPositions[i];
		// Spirit->m_Size = playerSize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Size = enemySize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Velocity = glm::vec2(PLAYER_VELOCITY); // misma velocidad que el jugador
		Spirit->m_Color = glm::vec3(1.0f); // a definir, podria cambiar el color de una textura de espiritu
		m_Entities.push_back(Spirit);
	}
}

void World::AddEntity(GameEntity* entity)
{
	//if (m_Entities == nullptr)
	//{
	//	return;
	//}

	//if (entity == nullptr)
	//{
	//	return;
	//}

	m_Entities.push_back(entity);
}
