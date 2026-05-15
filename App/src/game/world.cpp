#include "world.h"

constexpr int INITIAL_X_POS = 375;
constexpr int INITIAL_Y_POS = 275;
constexpr int INITIAL_PLAYER_X_SIZE = 80;
constexpr int INITIAL_PLAYER_Y_SIZE = 55;
constexpr int INITIAL_ENEMY_X_SIZE = 60;
constexpr int INITIAL_ENEMY_Y_SIZE = 55;
constexpr int PLAYER_VELOCITY = 0;

World::World()
{
}

World::~World()
{
}

void World::InitializeEntities()
{
	m_GameGrid = new Engine::TileManager(m_Entities);

	GameEntity* Player = CreatePlayer();

	glm::vec2 playerPosition(INITIAL_X_POS, INITIAL_Y_POS);
	glm::vec2 playerSize(INITIAL_PLAYER_X_SIZE,INITIAL_PLAYER_Y_SIZE);
	glm::vec2 enemySize(INITIAL_ENEMY_X_SIZE,INITIAL_ENEMY_Y_SIZE);

	Player->m_Id = PLAYER;
	Player->m_Position = playerPosition;
	Player->m_Size = playerSize;
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
		GameEntity* Spirit = CreateEnemy();

		Spirit->m_Id = SPIRIT;
		Spirit->m_Position = enemyPositions[i];
		// Spirit->m_Size = playerSize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Size = enemySize; // por ahora le mandamos el mismo tamaño del jugador
		Spirit->m_Velocity = glm::vec2(PLAYER_VELOCITY); // misma velocidad que el jugador
		Spirit->m_Color = glm::vec3(1.0f); // a definir, podria cambiar el color de una textura de espiritu
		m_Entities.push_back(Spirit);
	}
}

GameEntity* World::CreatePlayer() // aca uso el "patron factory" para crear una entidad de jugador
{
	PlayerInputComponent* input = new PlayerInputComponent();
	PlayerPhysicsComponent* physics = new PlayerPhysicsComponent();
	PlayerGraphicsComponent* graphics = new PlayerGraphicsComponent(physics);

	return new GameEntity(input,
		physics,
		graphics);
}

GameEntity* World::CreateEnemy() // aca uso el "patron factory" para crear una entidad de jugador
{
	SpiritInputComponent* input = new SpiritInputComponent();
	SpiritPhysicsComponent* physics = new SpiritPhysicsComponent();
	SpiritGraphicsComponent* graphics = new SpiritGraphicsComponent(physics);

	return new GameEntity(input,
		physics,
		graphics);
}
