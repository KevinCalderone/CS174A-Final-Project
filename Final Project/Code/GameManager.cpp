#include "GameManager.h"
#include <ctime>



GameManager::GameManager()
{
	m_w=m_a=m_s=m_d=m_i=m_j=m_k=m_l=m_auto = false;
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
	case ' ':
		m_auto = !m_auto; break;
	case 'w':
		m_w = true; break;
	case 's':
		m_s = true; break;
	case 'a':
		m_a = true; break;
	case 'd':
		m_d = true; break;
	case 'j':
		m_j = true; break;
	case 'i':
		m_i = true; break;
	case 'k':
		m_k = true; break;
	case 'l':
		m_l = true; break;
	}
}

void GameManager::callbackKeyUp(unsigned char key, int x, int y)
{
	switch(key) {
	case 'w':
		m_w = false; break;
	case 'a':
		m_a = false; break;
	case 's':
		m_s = false; break;
	case 'd':
		m_d = false; break;
	case 'i':
		m_i = false; break;
	case 'j':
		m_j = false; break;
	case 'k':
		m_k = false; break;
	case 'l':
		m_l = false; break;
	}
}

void GameManager::keyboardUpdate()
{
	m_player->setVelocity(vec3(m_d-m_a,0.0f,m_s-m_w));
	if(m_l-m_j==0 && m_k-m_i==0)
		m_player->setDirection(vec3(0.0f,0.0f,1.0f));
	else
		m_player->setDirection(vec3(m_l-m_j,0.0f,m_k-m_i));
}

GraphicsManager* GameManager::getGraphicsManager()
{
	return m_graphicsManager;
}

void GameManager::initEnviro() // gotta wait for implementation of EnviroObj & Ground
{
	m_ground = new Ground();
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "plane";	
	batch->m_effectParameters.m_modelviewMatrix =  mat4();
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f);
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.3f;
	batch->m_effectParameters.m_materialSpecularExponent = 6.0f;
	batch->m_effectParameters.m_materialGloss = 0.0f;
	batch->m_effectParameters.m_diffuseTexture = "stone";	
	batch->m_effectParameters.m_normalMap = "stoneNormal";
	m_ground->setRenderBatch(batch);
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
	m_player->setSize(1.f); // default?
	m_player->setSpeed(0.2f);
	m_player->setWeaponDelay(30); // default?
	m_player->setDirection(Angel::vec3(0.0f)); // default?
	m_player->setPosition(Angel::vec3(0.0f,0.0f,1.0f)); // default?
	m_player->addLife(3); // default?
}

void GameManager::initMonsters()
{
	// this is just a random spawning algorithm at the moment
	float x, z;
	srand((unsigned)time(0));
	do
	{
		x = 20 - rand()%40;
		z = 20 - rand()%40;
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
			monster->setSpeed(0.01);
			monster->setVelocity(normalize(*m_player->getPosition() - position));
			m_monsters.push_back(monster);
		}
		break;
	case BULLET:
		{
			Bullet* bullet = spawnBullet();
			bullet->setSize(0.1);
			bullet->setPosition(position);
			bullet->setSpeed(0.5);
			bullet->setVelocity(normalize(*m_player->getDirection()));
			m_bullets.push_back(bullet);
		}
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
	batch->m_geometryID = "cube";
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

Bullet* GameManager::spawnBullet()
{
	Bullet* bullet = new Bullet();
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "sphere";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 100.f;
	batch->m_effectParameters.m_diffuseTexture = "panda";	
	batch->m_effectParameters.m_normalMap = "monsterNormal";
	bullet->setRenderBatch(batch);
	return bullet;
}

void GameManager::Update()
{
	for(int i=0;i<m_monsters.size();i++){
		m_monsters.at(i)->setVelocity(normalize(*m_player->getPosition()-*m_monsters.at(i)->getPosition()));
		m_monsters.at(i)->Update(1.0f);
	}
	for(int i=0;i<m_bullets.size();i++)
		m_bullets.at(i)->Update(1.0f);
	m_player->Update(1.0f);
	if(m_auto && m_player->shoot())
		Spawn(BULLET,*m_player->getPosition());
}
	

void GameManager::Render()
{
	keyboardUpdate();
	Update();
	for(int i=0;i<m_monsters.size();i++)
		m_graphicsManager->Render(*m_monsters.at(i)->getRenderBatch());
	for(int i=0;i<m_bullets.size();i++)
		m_graphicsManager->Render(*m_bullets.at(i)->getRenderBatch());
	m_graphicsManager->Render(*m_player->getRenderBatch());
	m_graphicsManager->Render(*m_ground->getRenderBatch());
}

void GameManager::initGame()
{
	m_graphicsManager = new GraphicsManager("../Data/AssetLibrary.txt");
	initEnviro();
	initPlayer();
	initMonsters();
}

Player* GameManager::getPlayer()
{
	return m_player;
}