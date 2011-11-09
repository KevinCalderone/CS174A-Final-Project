#include "GameManager.h"
#include <ctime>



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
		case 'w':
			m_player->setPosition(vec3(m_player->getPosition()->x, m_player->getPosition()->y, m_player->getPosition()->z-1));
			break;
		case 's':
			m_player->setPosition(vec3(m_player->getPosition()->x, m_player->getPosition()->y, m_player->getPosition()->z+1));
			break;
		case 'a':
			m_player->setPosition(vec3(m_player->getPosition()->x-1, m_player->getPosition()->y, m_player->getPosition()->z));
			break;
		case 'd':
			m_player->setPosition(vec3(m_player->getPosition()->x+1, m_player->getPosition()->y, m_player->getPosition()->z));
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

void GameManager::initPlayer()
{
	m_player = spawnPlayer();
	m_player->setSize(2.f); // default?
	m_player->setWeaponDelay(100); // default?
	m_player->setDirection(Angel::vec3(0.0f)); // default?
	m_player->setPosition(Angel::vec3(0.0f,0.0f,0.0f)); // default?
	m_player->addLife(3); // default?
}

void GameManager::initMonsters()
{
	// this is just a random spawning algorithm at the moment
	float x, z;
	srand((unsigned)time(0));
	do
	{
		x = 7 - rand()%14;
		z = 7 - rand()%12;
		Spawn(MONSTER,Angel::vec3(x,0.0f,z),1);
	} while(m_monsters.size() < MONSTERCAP);
}

void GameManager::Spawn(objectType type, vec3 position, double size){
	switch(type){
	case PLAYER:
		break;
	case MONSTER:
		{
			Monster* monster = spawnMonster();
			monster->setSize(size);
			monster->setPosition(position);
			monster->setSpeed(size/4.0);
			monster->setVelocity(*m_player->getPosition() - position);
			m_monsters.push_back(monster);
		}
		break;
	case BULLET:
		break;
	case BUSH:
		break;
	}
}

Monster* GameManager::spawnMonster()
{
	Monster* monster = new Monster();
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "monster";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 0.1f;
	batch->m_effectParameters.m_diffuseTexture = "monster";	
	batch->m_effectParameters.m_normalMap = "monsterNormal";
	monster->setRenderBatch(batch);
	return monster;
}

Player* GameManager::spawnPlayer()
{
	Player* player = new Player();
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "cone";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 0.1f;
	batch->m_effectParameters.m_diffuseTexture = "monster";	
	batch->m_effectParameters.m_normalMap = "monsterNormal";
	player->setRenderBatch(batch);
	return player;
}

void GameManager::Update()
{
	for(int i=0;i<m_monsters.size();i++){
		m_monsters.at(i)->setVelocity(*m_player->getPosition() - *m_monsters.at(i)->getPosition());
		m_monsters.at(i)->Update(1.0f);
	}
	m_player->Update(1.0f);
}
	

void GameManager::Render()
{
	Update();
	for(int i=0;i<m_monsters.size();i++)
		m_graphicsManager->Render(*m_monsters.at(i)->getRenderBatch());
	m_graphicsManager->Render(*m_player->getRenderBatch());
}

void GameManager::initGame()
{
	m_graphicsManager = new GraphicsManager("../Data/AssetLibrary.txt");
	initEnviro();
	initPlayer();
	initMonsters();
}