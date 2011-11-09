#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::callbackKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:	// esc
			exit(0);
			break;
		case '`':
			m_graphicsManager->ReloadAssets();
			break;
	}
}

GraphicsManager* GameManager::getGraphicsManager()
{
	return m_graphicsManager;
}

void GameManager::initEnviro() // gotta wait for implementation of EnviroObj & Ground
{
	//m_ground = new Ground();
	//m_enviro.push_back(new EnviroObj(/* type, position */)); // OK do we want to have some sort of file specify		\
																all the parameters for where every tree/rock/etc	\
																is located at? Or do we want initEnviro to just		\
																manually push_back one EnviroObj at a time? Also	\
																in either case EnviroObj must have a constructor	\
																which can let it know if it's a rock, tree, etc.
}

void GameManager::initPlayer() // gotta wait for implementation of Player
{
	m_player = new Player();
	m_player->setWeaponDelay(100); // default?
	m_player->setDirection(Angel::vec3(0.0f)); // default?
	m_player->setPosition(Angel::vec3(0.0f,0.0f,0.0f)); // default?
	m_player->setSize(10.f); // default?
	m_player->addLife(3); // default?
}

void GameManager::initMonsters() // gotta wait for implementation of Monster
{
	// this is just a random spawning algorithm at the moment
	float x, y;
	//do
	//{
	//	x = 12 - rand()%24; // horizontal screen range of 20 units? Left = -10, Right = +10
	//	y = 12; // vertical screen range of 20 units? Top = +10, Bottom = -10
	//	Spawn(MONSTER,Angel::vec3(x,y,0.0f),rand()%20);
	//} while(m_monsters.size() <= MONSTERCAP);
	//Spawn(MONSTER,Angel::vec3(0.0f,0.0f,0.0f)); //Needs to be changed, of course.							\
													Again, do we want a file to specify, or do it manually?	\
													I think manually would be better here, since we could	\
													then randomly create the position of each Monster.
}

void GameManager::Spawn(objectType type, vec3 position, double size){
	/*switch(type){
	case PLAYER:
		break;
	case MONSTER:
		{
			Monster* monster = spawnMonster();
			monster->setPosition(position);
			monster->setSize(size);
			monster->setSpeed(size/2.0);
			monster->setVelocity(position - *m_player->getPosition());
		}
		break;
	case BULLET:
		break;
	case BUSH:
		break;
	}*/
}

Monster* spawnMonster()
{
	Monster* monster = new Monster();
	//monster->setRenderBatch
	return monster;
}
void GameManager::initGame()
{
	m_graphicsManager = new GraphicsManager("../Data/AssetLibrary.txt");
	initEnviro();
	initPlayer();
	initMonsters();
	//m_graphicsManager->Render(*m_player->getRenderBatch());
}