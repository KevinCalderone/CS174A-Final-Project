#include "GameManager.h"
#include <ctime>



GameManager::GameManager()
{
	m_w=m_a=m_s=m_d=m_j=m_l=m_auto = false;
	angle = 0.0f;
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
	case 'j':
		m_j = false; break;
	case 'l':
		m_l = false; break;
	}
}

void GameManager::keyboardUpdate()
{
	m_player->setVelocity(vec3(m_d-m_a,0.0f,m_s-m_w));
	if(m_j) angle += 0.05;
	if(m_l) angle -= 0.05;
	if(angle>360 || angle<-360) angle = 0.0;
	m_player->setDirection(vec3(-sin(angle),0.0f,-cos(angle)));
	m_player->getBoundingBox()->rotate((m_l-m_j)*(0.05/DegreesToRadians));
}

GraphicsManager* GameManager::getGraphicsManager()
{
	return m_graphicsManager;
}

void GameManager::initEnviro() // gotta wait for implementation of EnviroObj & Ground
{
	m_ground = new Ground();

	//m_enviro.push_back(new EnviroObj(/* type, position */)); // OK do we want to have some sort of file specify		\
																all the parameters for where every tree/rock/etc	\
																is located at? Or do we want initEnviro to just		\
																manually push_back one EnviroObj at a time? Also	\
																in either case EnviroObj must have a constructor	\
																which can let it know if it's a rock, tree, etc.
}

void GameManager::initPlayer()
{
	m_player = new Player(Angel::vec3(0.0f,0.0f,1.0f), Angel::vec3(0.0f), 1.0f, 0.2f, 3, 30);

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
			Monster* monster = new Monster(position, normalize(*m_player->getPosition() - position), size, 0.01);
			m_monsters.push_back(monster);
		}
		break;
	case BULLET:
		{
			Bullet* bullet = new Bullet(*m_player->getPosition(), normalize(*m_player->getDirection()), 0.1, 0.5);
			m_bullets.push_back(bullet);
		}
		break;
	case BUSH:
		break;
	}
}

void GameManager::Delete(objectType type, int index)
{
	switch(type)
	{
	case PLAYER:
		delete m_player; break;
	case MONSTER:
		m_monsters.erase(m_monsters.begin()+index); break;
	case BULLET:
		m_bullets.erase(m_bullets.begin()+index); break;
	}
}

void GameManager::CollisionDetection()
{
	/*if(collision(*m_player->getBoundingBox(),*m_monsters.at(0)->getBoundingBox()))
		std::cout << "COLLISION BITCH!" << std::endl;
	else
		std::cout << "You're good!" << std::endl;*/
	
	for(int j=0; j<m_bullets.size();j++){
	for(int i=0; i<m_monsters.size();i++)
	{
		if(m_bullets.size()!=0 && m_monsters.size()!=0
			&& collision(*m_bullets.at(j)->getBoundingBox(), *m_monsters.at(i)->getBoundingBox()))
		{
			Delete(MONSTER,i);
			Delete(BULLET,j);
			i--;
			j--;
		}
	}
	}

	for(int k=0; k<m_monsters.size();k++)
	{
		if(collision(*m_monsters.at(k)->getBoundingBox(),*m_player->getBoundingBox()))
			std::cout << "YOU GOT KILLED BY: " << k << std::endl;
	}
	
}

void GameManager::Update()
{
	if(m_auto && m_player->shoot())
		Spawn(BULLET,*m_player->getPosition());

	CollisionDetection();

	for(int i=0;i<m_monsters.size();i++){
		//m_monsters.at(i)->setVelocity(*m_player->getDirection());
		m_monsters.at(i)->setVelocity(normalize(*m_player->getPosition()-*m_monsters.at(i)->getPosition()));
		m_monsters.at(i)->Update(1.0f);
	}
	for(int i=0;i<m_bullets.size();i++)
	{
		if(m_bullets.size() != 0){
			m_bullets.at(i)->Update(1.0f);
			if(length(*m_bullets.at(i)->getPosition()-*m_player->getPosition()) > 100){
				Delete(BULLET,i); i--;std::cout << i << std::endl;}
		}
	}
	m_player->Update(1.0f);
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