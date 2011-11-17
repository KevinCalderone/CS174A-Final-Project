#include "GameManager.h"
#include <ctime>
#include <vector>



GameManager::GameManager()
{
	m_w=m_a=m_s=m_d=m_j=m_l=m_auto=m_godmode = false;
	angle = 0.0f;
	m_score = m_god = 0;
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
	float ad = m_d-m_a;
	float ws = m_s-m_w;

	if(m_player->getPosition()->x <= -400)
		ad = m_d;
	if(m_player->getPosition()->x >= 400)
		ad = -m_a;
	if(m_player->getPosition()->z <= -300)
		ws = m_s;
	if(m_player->getPosition()->z >= 300)
		ws = -m_w;

	for(int i=0;i<m_enviro.size();i++)
	{
		if(length(*m_enviro.at(i)->getPosition()-*m_player->getPosition()) < 10 && 
			collision(*m_enviro.at(i)->getBoundingBox(),*m_player->getBoundingBox()))
		{
			vec3* op = m_enviro.at(i)->getPosition();
			vec3* pp = m_player->getPosition();
			if(op->x <= pp->x)
				if((op->z <= (pp->z + (pp->x - op->x))) && (op->z >= (pp->z - (pp->x - op->x))))
					ad = m_d;
			if(op->x > pp->x)
				if((op->z <= (pp->z + (op->x - pp->x))) && (op->z >= (pp->z - (op->x - pp->x))))
					ad = -m_a;
			if(op->z <= pp->z)
				if((op->x <= (pp->x + (pp->z - op->z))) && (op->x >= (pp->x - (pp->z - op->z))))
					ws = m_s;
			if(op->z > pp->z)
				if((op->x <= (pp->x + (op->z - pp->z))) && (op->x >= (pp->x - (op->z - pp->z))))
					ws = -m_w;
		}
	}


	m_player->setVelocity(vec3(ad,0.0f,ws));
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

	//Spawn(TREE,vec3(10,0,0),2.f);
	//Spawn(ROCK,vec3(5,0,0),1.f);

	float x, z;
	srand((unsigned)time(0));
	do
	{
		do
		{
			x = 200 - rand()%400;
			z = 150 - rand()%300;
		} while((x < 4 && x > -4) && (z < 4 && z > -4));
		Spawn(TREE,Angel::vec3(x,1.0f,z),2);
	} while(m_enviro.size() < 600);

	do
	{
		do
		{
			x = 200 - rand()%400;
			z = 150 - rand()%300;
		} while((x < 4 && x > -4) && (z < 4 && z > -4));
		Spawn(ROCK,Angel::vec3(x,1.0f,z),0.5);
	} while(m_enviro.size() < 1200);
	//m_enviro.push_back(new EnviroObj(/* type, position */)); // OK do we want to have some sort of file specify		\
																all the parameters for where every tree/rock/etc	\
																is located at? Or do we want initEnviro to just		\
																manually push_back one EnviroObj at a time? Also	\
																in either case EnviroObj must have a constructor	\
																which can let it know if it's a rock, tree, etc.
}

void GameManager::initPlayer()
{
	m_player = new Player(Angel::vec3(0.0f,0.0f,1.0f), Angel::vec3(0.0f), 1.0f, 0.2f, 3, 20);

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

void GameManager::Spawn(objectType type, vec3 position, float size){
	switch(type){
	case PLAYER:
		break;
	case MONSTER:
		{
			Monster* monster = new Monster(position, normalize(*m_player->getPosition() - position), size, 0.01);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(collision(*monster->getBoundingBox(), *m_enviro.at(i)->getBoundingBox()))
					allowed = false;
			if(allowed)
				m_monsters.push_back(monster);
			else
				Spawn(MONSTER,vec3(position.x+3,0.f,position.z+3),size);
		}
		break;
	case BULLET:
		{
			Bullet* bullet = new Bullet(*m_player->getPosition(), normalize(*m_player->getDirection()), 0.1, 0.5);
			m_bullets.push_back(bullet);
		}
		break;
	case TREE:
	case BUSH:
	case ROCK:
		{
			EnviroObj* obj = new EnviroObj(type, position, vec3(0,0,1), size);
			//BoundingBox* objbb = new BoundingBox(vec2(position.x,position.z),4.f,4.f);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(length(position-*m_enviro.at(i)->getPosition()) < 8)
					allowed = false;
			if(allowed)
				m_enviro.push_back(obj);
			else
				delete obj;
			//delete objbb;
		}
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
			Delete(BULLET,j);
			vec3 monsp = *m_monsters.at(i)->getPosition();
			float monss = m_monsters.at(i)->getSize();
			vec3 smons1p = monsp + (monss * normalize(normal(monsp-*m_player->getPosition())));
			vec3 smons2p = monsp + (-monss * normalize(normal(monsp-*m_player->getPosition())));
			Delete(MONSTER,i);
			if(monss > 0.5)
			{
				Spawn(MONSTER,smons1p,monss/1.5);
				Spawn(MONSTER,smons2p,monss/1.5);
			}
			i = m_monsters.size();
			j--;
			m_score++;
		}
	}
	}

	for(int j=0; j<m_bullets.size();j++){
	for(int i=0; i<m_enviro.size();i++)
	{
		if(m_bullets.size()!=0 && collision(*m_bullets.at(j)->getBoundingBox(), *m_enviro.at(i)->getBoundingBox()))
		{
			Delete(BULLET,j);
			i = m_enviro.size();
			j--;
		}
	}
	}

	if(m_godmode)
		m_god--;
	if(m_god==0)
		m_godmode = false;
	for(int k=0; k<m_monsters.size();k++)
	{
		if(collision(*m_monsters.at(k)->getBoundingBox(),*m_player->getBoundingBox())){
			if(!m_godmode){
				m_godmode = true;
				m_god = 100;
				std::cout << "YOU GOT HIT BY: " << k << std::endl;
				if(m_player->kill()){
					std::cout << "YOU'RE DEAD!" << std::endl;
					system("PAUSE");
				}
			}
		}
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
			if(length(*m_bullets.at(i)->getPosition()-*m_player->getPosition()) > 50){
				Delete(BULLET,i); i--;}
		}
	}
	for(int i=0;i<m_enviro.size();i++)
		m_enviro.at(i)->Update(1.0f);
	m_player->Update(1.0f);
}
	

void GameManager::Render()
{
	keyboardUpdate();
	updateCamera();
	Update();
	for(int i=0;i<m_monsters.size();i++)
		m_graphicsManager->Render(*m_monsters.at(i)->getRenderBatch());
	for(int i=0;i<m_bullets.size();i++)
		m_graphicsManager->Render(*m_bullets.at(i)->getRenderBatch());
	for(int i=0;i<m_enviro.size();i++)
		if(length(*m_enviro.at(i)->getPosition()-*m_player->getPosition()) <= 50)
			m_graphicsManager->Render(*m_enviro.at(i)->getRenderBatch());
	m_graphicsManager->Render(*m_player->getRenderBatch());
	m_graphicsManager->Render(*m_ground->getRenderBatch());
	m_graphicsManager->SwapBuffers();
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

void GameManager::SetCameraOrthogonal()
{
	RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();
	renderParameters.m_projectionMatrix = mat4();
}

void GameManager::SetupCamera(vec4 playerPos)
{
	vec4 playerPosition = playerPos;
	vec4 eyePosition = playerPosition + vec4(0.0f, 15.0f, 15.0f, 0.0f);
	RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();

	renderParameters.m_eyePosition = vec3(eyePosition.x, eyePosition.y, eyePosition.z);
	renderParameters.m_projectionMatrix = 
		Angel::Perspective(45.0f, 4.0f/3.0f, 0.5f, 50.0f) * 
		Angel::LookAt(eyePosition, playerPosition, vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

void GameManager::updateCamera()
{
	m_graphicsManager->ClearScreen();
	
	{
		static float theta = 0.0f;
		theta += 1.0f;

		SetupCamera(*m_player->getPosition());

		RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();

		// Position lights at player postion
		renderParameters.m_pointLightPosition[0] = *m_player->getPosition() + vec3(0.0f, 1.5f, -1.5f);
		renderParameters.m_pointLightPosition[1] = *m_player->getPosition() + vec3(0.0f, 0.5f, -2.5f);
		
		// Muzzle flash
		float flashIntensity = cos((3.14159 / 2.0f) * (fmod(theta, 20.0f) < 13.0f ? fmod(theta, 20.0f) / 13.0f : 1.0f))*1.5;
		renderParameters.m_pointLightDiffuse[1] = vec3(3.0f, 3.0f, 0.0f) * flashIntensity;
		renderParameters.m_pointLightSpecular[1] = vec3(2.0f, 2.0f, 0.0f) * flashIntensity;
		renderParameters.m_pointLightRange[1] = 8.0f * flashIntensity;
		renderParameters.m_pointLightFalloff[1] = 2.0f * flashIntensity;

		// Flickering Torch
		renderParameters.m_pointLightRange[0] = 11.0f + 2.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f ;
		renderParameters.m_pointLightFalloff[0] = 2.0f + 1.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f;

		//Render();
	}

	// This is just for testing until you get this incorportated into GameManager
}