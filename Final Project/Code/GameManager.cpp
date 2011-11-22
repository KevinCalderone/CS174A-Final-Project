#include "GameManager.h"
#include <ctime>
#include <vector>

const bool BBDEBUG = false;

GameManager::GameManager()
{
	m_w=m_a=m_s=m_d=m_j=m_l=m_auto=m_godmode=m_pause = false;
	angle = 0.0f;
	m_score = m_god = 0;
	m_bulletchannel = m_monschannel = m_bgchannel = 0;
	m_timer = NULL;
}

GameManager::~GameManager()
{
	// need to delete all monsters, bullets, enviro, bgenviro, m_ground, m_graphicsmanagers, m_system;

	if(m_ground)
		delete m_ground;

	if(m_player)
		delete m_player;

	if(m_graphicsManager)
		delete m_graphicsManager;

	// vector::clear should delete all objects within
	m_monsters.clear();
	m_bullets.clear();
	m_enviro.clear();
	m_bgenviro.clear();

	
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
	case 13:
		if(!m_pause) break;
		ResetGame();
		break;
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

	if(m_pp.x <= -400)
		ad = m_d;
	if(m_pp.x >= 400)
		ad = -m_a;
	if(m_pp.z <= -300)
		ws = m_s;
	if(m_pp.z >= 300)
		ws = -m_w;

	for(int i=0;i<m_enviro.size();i++)
	{
		if(length(*m_enviro.at(i)->getPosition()-m_pp) < 10 && 
			collision(*m_enviro.at(i)->getBoundingBox(),*m_player->getBoundingBox()))
		{
			if(relativePosition(*m_player,*m_enviro.at(i)) == LEFT)
				ad = m_d;
			if(relativePosition(*m_player,*m_enviro.at(i)) == RIGHT)
				ad = -m_a;
			if(relativePosition(*m_player,*m_enviro.at(i)) == UP)
				ws = m_s;
			if(relativePosition(*m_player,*m_enviro.at(i)) == DOWN)
				ws = -m_w;
		}
	}

	if(ad!=0.0 && ws!=0.0)
		m_player->setVelocity(normalize(vec3(ad,0.0f,ws)));
	else
		m_player->setVelocity((vec3(ad,0.0f,ws)));

	if(m_j) angle += 0.08  * m_delta;
	if(m_l) angle -= 0.08 * m_delta;
	if(angle>360) angle -= 360;
	if (angle<-360) angle += 360;
	m_player->setDirection(vec3(-sin(angle),0.0f,-cos(angle)));
	m_player->getBoundingBox()->rotate((m_l-m_j)*(0.05/DegreesToRadians));
}

void GameManager::ResetGame()
{
	m_w=m_a=m_s=m_d=m_j=m_l=m_auto=m_godmode=m_pause = false;
	angle = 0.0f;
	m_score = m_god = 0;
	m_bulletchannel = m_monschannel = m_bgchannel = 0;

	// need to delete all monsters, bullets, enviro, bgenviro, m_ground, m_graphicsmanagers, m_system;

	if(m_ground)
		delete m_ground;

	if(m_player)
		delete m_player;

	if(m_graphicsManager)
		delete m_graphicsManager;

	if(m_timer)
		delete m_timer;
	m_timer = NULL;

	// vector::clear should delete all objects within
	m_monsters.clear();
	m_bullets.clear();
	m_enviro.clear();
	m_bgenviro.clear();

	m_system->close();


	initGame();
}

void GameManager::initParameters()
{
	RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();
	renderParameters.m_lightDirection = vec3(1.0f, 2.0f, 2.0f);
	renderParameters.m_lightAmbient = vec3(0.5f, 0.5f, 0.7f) * 0.6f;
	renderParameters.m_lightDiffuse = vec3(1.0f, 1.0f, 0.6f) * 0.0f;
	renderParameters.m_lightSpecular = vec3(1.0f, 1.0f, 0.7f) * 0.0f;
	renderParameters.m_environmentMap = "envMap";
	
	renderParameters.m_pointLightAmbient[0] = vec3(0.1f, 0.0f, 0.0f);
	renderParameters.m_pointLightDiffuse[0] = vec3(1.5f, 0.5f, 0.0f);
	renderParameters.m_pointLightSpecular[0] = vec3(2.5f, 1.5f, 0.0f);
	renderParameters.m_pointLightRange[0] = 12.0f;
	renderParameters.m_pointLightFalloff[0] = 5.0f;
	
	renderParameters.m_pointLightPosition[1] = vec3(5.0f, 1.0f, 0.0f);
	renderParameters.m_pointLightDiffuse[1] = vec3(0.0f, 0.0f, 0.0f);
	renderParameters.m_pointLightSpecular[1] = vec3(0.0f, 0.0f, 0.0f);
	renderParameters.m_pointLightRange[1] = 10.0f;
	renderParameters.m_pointLightFalloff[1] = 2.0f;
	
	//renderParameters.m_pointLightPosition[2] = vec3(0.0f, 1.0f, 5.0f);
	//renderParameters.m_pointLightDiffuse[2] = vec3(0.0f, 1.0f, 0.0f);
	//renderParameters.m_pointLightSpecular[2] = vec3(0.0f, 1.0f, 0.0f);
	//renderParameters.m_pointLightRange[2] = 8.0f;
	//renderParameters.m_pointLightFalloff[2] = 2.0f;
	
	// No color correction
	renderParameters.m_colorCorrection = mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void GameManager::initEnviro() // gotta wait for implementation of EnviroObj & Ground
{
	m_ground = new Ground();

	float x, z;
	srand((unsigned)time(0));
	for(int i=1;i<=16;i++)
	{
		do
		{
			do
			{
				x = -400+ 50*i - rand()%50;
				z = 300 - rand()%600;
			} while((x < 4 && x > -4) && (z < 4 && z > -4));
			Spawn(BUSH,Angel::vec3(x,0.0f,z),2);
		} while(m_bgenviro.size() < 500*i);
	}

	do
	{
		do
		{
			x = 400 - rand()%800;
			z = 300 - rand()%600;
		} while((x < 4 && x > -4) && (z < 4 && z > -4));
		Spawn(LEAVES,Angel::vec3(x,0.0f,z),1.7);
		Spawn(TREE,Angel::vec3(x,0.0f,z),1.7);
	} while(m_enviro.size() < 300);

	do
	{
		do
		{
			x = 400 - rand()%800;
			z = 300 - rand()%600;
		} while((x < 4 && x > -4) && (z < 4 && z > -4));
		Spawn(ROCK,Angel::vec3(x,0.0f,z),0.015);
	} while(m_enviro.size() < 600);

	do
	{
		do
		{
			x = 400 - rand()%800;
			z = 300 - rand()%600;
		} while((x < 4 && x > -4) && (z < 4 && z > -4));
		Spawn(CRATE,Angel::vec3(x,0.0f,z),1.0);
	} while(m_powerups.size() < 100);

	for(int i=0;i<m_bgenviro.size();i++)
		m_bgenviro.at(i)->Update(1.0f);
	for(int i=0;i<m_enviro.size();i++)
		m_enviro.at(i)->Update(1.0f);

	
}

void GameManager::initPlayer()
{
	m_player = new Player(Angel::vec3(0.0f,0.0f,1.0f), Angel::vec3(0.0f), 0.7f, 0.2f, 3, 5);
	m_pp = *m_player->getPosition();
	if(BBDEBUG) m_player->getRenderBatch()->m_effectParameters.m_materialOpacity = 0.5f;
}

void GameManager::initMonsters()
{
	// this is just a random spawning algorithm at the moment
	/*float x, z;
	srand((unsigned)time(0));
	do
	{
		x = 20 - rand()%40;
		z = 20 - rand()%40;
		Spawn(MONSTER,Angel::vec3(x,0.0f,z),0.6);
	} while(m_monsters.size() < MONSTERCAP);*/
	spawnMonsters();
}

void GameManager::Spawn(objectType type, vec3 position, float size){
	switch(type){
	case PLAYER:
		break;
	case MONSTER:
		{
			Monster* monster = new Monster(position, normalize(m_pp - position), size, 0.15);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(collision(*monster->getBoundingBox(), *m_enviro.at(i)->getBoundingBox()))
					allowed = false;
			if(allowed)
				m_monsters.push_back(monster);
			else
			{
				int dx = 1 - 2*(m_pp.x > position.x);
				int dz = 1 - 2*(m_pp.z > position.z);
				Spawn(MONSTER,vec3(position.x+dx,0.f,position.z+dz),size);
			}
		}
		break;
	case BULLET:
		{
			Bullet* bullet = new Bullet(m_pp, normalize(*m_player->getDirection()), 1.0f, 0.6 +
				length(*m_player->getVelocity()));
			m_bullets.push_back(bullet);
			if(m_player->getWeapon()==SHOTTY)
			{
				Bullet* bullet2 = new Bullet(m_pp, normalize(*m_player->getDirection()+0.2*normal(*m_player->getDirection())), 0.1, 0.6 +
					length(*m_player->getVelocity()));
				m_bullets.push_back(bullet2);

				Bullet* bullet3 = new Bullet(m_pp, normalize(*m_player->getDirection()-0.2*normal(*m_player->getDirection())), 0.1, 0.6 +
					length(*m_player->getVelocity()));
				m_bullets.push_back(bullet3);
			}
		}
		break;
	case LEAVES:
		{
			EnviroObj* obj = new EnviroObj(type, position, vec3(0,0,1), size);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(length(position-*m_enviro.at(i)->getPosition()) < 8)
					allowed = false;
			if(allowed)
				m_bgenviro.push_back(obj);
			else
				delete obj;
		}
		break;
	case TREE:
		{
			EnviroObj* obj = new EnviroObj(type, position, vec3(0,0,1), size);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(length(position-*m_enviro.at(i)->getPosition()) < 8)
					allowed = false;
			if(allowed)
				m_enviro.push_back(obj);
			else
				delete obj;
		}
		break;
	case BUSH:
		{
			EnviroObj* obj = new EnviroObj(type, position, vec3(0,0,1), size);
			m_bgenviro.push_back(obj);
		}
		break;
	case ROCK:
		{
			EnviroObj* obj = new EnviroObj(type, position, vec3(0,0,1), size);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(length(position-*m_enviro.at(i)->getPosition()) < 8)
					allowed = false;
			if(allowed)
				m_enviro.push_back(obj);
			else
				delete obj;
		}
		break;
	case CRATE:
		{
			Crate* obj = new Crate(type, position, vec3(0,0,1), size);
			bool allowed = true;
			for(int i=0;i<m_enviro.size();i++)
				if(length(position-*m_enviro.at(i)->getPosition()) < 5)
					allowed = false;
			for(int i=0;i<m_powerups.size();i++)
				if(length(position-*m_powerups.at(i)->getPosition()) < 50)
					allowed = false;
			if(allowed)
				m_powerups.push_back(obj);
			else
				delete obj;
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
	case CRATE:
		m_powerups.erase(m_powerups.begin()+index); break;
	}
}

void GameManager::CollisionDetection()
{
	/*if(collision(*m_player->getBoundingBox(),*m_monsters.at(0)->getBoundingBox()))
		std::cout << "COLLISION BITCH!" << std::endl;
	else
		std::cout << "You're good!" << std::endl;*/

	for(int j=0; j<m_bullets.size();j++){
	for(int i=0; i<m_monsters.size();i++){
		if(m_bullets.size()!=0 && m_monsters.size()!=0
			&& length(*m_bullets.at(j)->getPosition() - *m_monsters.at(i)->getPosition()) < 3
			&& collision(*m_bullets.at(j)->getBoundingBox(), *m_monsters.at(i)->getBoundingBox()))
		{
			playSound(MONSDEATH);
			Delete(BULLET,j);
			vec3 monsp = *m_monsters.at(i)->getPosition();
			float monss = m_monsters.at(i)->getSize();
			vec3 smons1p = monsp + (monss * normalize(normal(monsp-m_pp)));
			vec3 smons2p = monsp + (-monss * normalize(normal(monsp-m_pp)));
			Delete(MONSTER,i);
			if(monss > 0.4)
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
	for(int i=0; i<m_enviro.size();i++){
		if(m_bullets.size()!=0 
			&& length(*m_bullets.at(j)->getPosition() - *m_enviro.at(i)->getPosition()) < 3
			&& collision(*m_bullets.at(j)->getBoundingBox(), *m_enviro.at(i)->getBoundingBox()))
		{
			Delete(BULLET,j);
			i = m_enviro.size();
			j--;
		}
	}
	}

	for(int j=0; j<m_bullets.size();j++){
	for(int i=0; i<m_powerups.size();i++){
		if(m_bullets.size()!=0 
			&& length(*m_bullets.at(j)->getPosition() - *m_powerups.at(i)->getPosition()) < 3)///////////
		{
			Delete(BULLET,j);
			i = m_powerups.size();
			j--;
		}
	}
	}

	if(m_godmode)
		m_god--;
	if(m_god==0){
		m_player->getRenderBatch()->m_effectParameters.m_materialOpacity = 1.0f;
		m_player->setSpeed(0.2f);
		m_godmode = false;}

	for(int k=0; k<m_monsters.size();k++){
		if(collision(*m_monsters.at(k)->getBoundingBox(),*m_player->getBoundingBox())){
			if(!m_godmode){
				m_godmode = true;
				m_player->getRenderBatch()->m_effectParameters.m_materialOpacity = 0.5f;
				m_player->setSpeed(0.3f);
				m_god = 100;
				std::cout << "YOU GOT HIT BY: " << k << std::endl;
				if(m_player->kill()){
					std::cout << "YOU'RE DEAD!" << std::endl;
					m_pause = true;
				}
			}
			return;
		}
	}

	for(int i=0; i<m_powerups.size(); i++)
		if(length(m_pp - *m_powerups.at(i)->getPosition()) < 2){
			m_player->setWeapon(SHOTTY);
			Delete(CRATE, i);}
}

void GameManager::Update()
{
//	std::cout << (*m_player->getPosition()-*m_powerups.at(0)->getPosition()) << std::endl;
	if(m_pause)
		return;

	if(m_monsters.size() < MONSTERCAP)
		spawnMonsters();

	if(m_auto && m_player->shoot()){
		if(m_player->getWeapon() == SHOTTY)
			//std::cout << "BANG!" << std::endl;
			playSound(SHOTGUN);
		else
			playSound(MACHINEGUN);
		Spawn(BULLET,m_pp);}

	CollisionDetection();


	for(int i=0;i<m_powerups.size();i++)
		m_powerups.at(i)->Update(m_delta);

	for(int i=0;i<m_monsters.size();i++){

			m_monsters.at(i)->setVelocity(normalize(m_pp-*m_monsters.at(i)->getPosition()));

	for(int k=0;k<m_monsters.size();k++){
		if(i != k){
			vec3 temp = *m_monsters.at(i)->getPosition()-*m_monsters.at(k)->getPosition();
			GLfloat len = length(temp);
			if(len < 1)
			{
				m_monsters.at(i)->setVelocity(normalize(*m_monsters.at(i)->getVelocity() + (1-len)*temp));
			}
		}
	}

	for(int j=0;j<m_enviro.size();j++){
		if((length(*m_enviro.at(j)->getPosition()-*m_monsters.at(i)->getPosition()) < 2) && // this 2 will have to depend on sizes
			acos(dot(normalize(*m_monsters.at(i)->getPosition()-*m_enviro.at(j)->getPosition()),
				normalize(*m_monsters.at(i)->getPosition()-m_pp)))/DegreesToRadians < 90)
		{
			m_monsters.at(i)->setVelocity(monsColDirection(m_monsters.at(i),m_enviro.at(j)));
		}
	}

	for(int j=0;j<m_powerups.size();j++){
		if((length(*m_powerups.at(j)->getPosition()-*m_monsters.at(i)->getPosition()) < 2) &&
			acos(dot(normalize(*m_monsters.at(i)->getPosition()-*m_powerups.at(j)->getPosition()),
				normalize(*m_monsters.at(i)->getPosition()-m_pp)))/DegreesToRadians < 90)
		{
			m_monsters.at(i)->setVelocity(monsColDirection(m_monsters.at(i),m_powerups.at(j)));
		}
	}

		m_monsters.at(i)->Update(m_delta);
	}

	for(int i=0;i<m_bullets.size();i++)
	{
		if(m_bullets.size() != 0){
			m_bullets.at(i)->Update(m_delta);
			if(length(*m_bullets.at(i)->getPosition()-m_pp) > 25){
				Delete(BULLET,i); i--;}
		}
	}
	m_player->Update(m_delta);
	m_pp = *m_player->getPosition();
}
	

void GameManager::Render()
{
	if(m_timer == NULL)
		m_timer = new Timer();

	m_delta = m_timer->GetElapsedTime() * 60.0f;
	m_timer->Reset();

	keyboardUpdate();
	updateCamera();
	Update();
	for(int i=0;i<m_powerups.size();i++)
		m_graphicsManager->Render(*m_powerups.at(i)->getRenderBatch());
	for(int i=0;i<m_monsters.size();i++){
		m_graphicsManager->Render(*m_monsters.at(i)->getRenderBatch());
		if(BBDEBUG) m_graphicsManager->Render(*m_monsters.at(i)->getBoundingBox()->getRenderBatch());}
	for(int i=0;i<m_bullets.size();i++)
		m_graphicsManager->Render(*m_bullets.at(i)->getRenderBatch());
	for(int i=0;i<m_enviro.size();i++)
		if(length(*m_enviro.at(i)->getPosition()-m_pp) <= 50){
			m_graphicsManager->Render(*m_enviro.at(i)->getRenderBatch());
			if(BBDEBUG) m_graphicsManager->Render(*m_enviro.at(i)->getBoundingBox()->getRenderBatch());}
	if(!(BBDEBUG))
		renderBG();
	m_graphicsManager->Render(*m_player->getRenderBatch());
	if(BBDEBUG) m_graphicsManager->Render(*m_player->getBoundingBox()->getRenderBatch());
	m_graphicsManager->Render(*m_ground->getRenderBatch());

	// render the hud too
	RenderHUD();

	m_graphicsManager->SwapBuffers();
}

void GameManager::initSounds()
{
	FMOD::System_Create(&m_system);
	m_system->init(3, FMOD_INIT_NORMAL, 0);
	m_system->createStream("../Data/Sounds/MachinegunFire.wav", FMOD_HARDWARE | FMOD_2D, 0, &m_sounds[MACHINEGUN]);
	m_system->createStream("../Data/Sounds/ShotgunFire.wav", FMOD_HARDWARE | FMOD_2D, 0, &m_sounds[SHOTGUN]);
	m_system->createStream("../Data/Sounds/BGMusic.mp3", FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &m_sounds[BGMUSIC]);
	m_system->createStream("../Data/Sounds/MonsHit.wav", FMOD_HARDWARE | FMOD_2D, 0, &m_sounds[MONSDEATH]);
	playSound(BGMUSIC);
}

void GameManager::playSound(soundType sound)
{
	FMOD::Channel *temp;
	switch(sound){
	case MACHINEGUN:
	case SHOTGUN:	temp = m_bulletchannel; break;
	case MONSDEATH: temp = m_monschannel; break;
	case BGMUSIC:	temp = m_bgchannel; break;}
	m_system->playSound(FMOD_CHANNEL_FREE, m_sounds[sound], false, &temp);
}

void GameManager::initGame()
{
	std::cout << "INITIALIZING GAME";
	m_graphicsManager = new GraphicsManager("../Data/AssetLibrary.txt");
	std::cout << ".";
	initSounds();
	initParameters();
	std::cout << ".";
	initEnviro();
	std::cout << ".";
	initPlayer();
	initMonsters();
	std::cout << std::endl << "...GAME INITIALIZED!" << std::endl << std::endl;
}

void GameManager::SetCameraOrthogonal()
{
	RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();
	renderParameters.m_projectionMatrix = Ortho(-10.0, 10.0, -10.0, 10.0, 0.0, 1.0);
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

		SetupCamera(m_pp);

		RenderParameters& renderParameters = m_graphicsManager->GetRenderParameters();

		// Position lights at player postion
		renderParameters.m_pointLightPosition[0] = m_pp + vec3(0.0f, 1.5f, -1.5f);
		renderParameters.m_pointLightPosition[1] = m_pp + vec3(0.0f, 0.5f, -2.5f);
		
		// Muzzle flash
		float flashIntensity = 1;//cos((3.14159 / 2.0f) * (fmod(theta, 20.0f) < 13.0f ? fmod(theta, 20.0f) / 13.0f : 1.0f))*1.5;
		renderParameters.m_pointLightDiffuse[1] = vec3(3.0f, 3.0f, 0.3f) * flashIntensity;
		renderParameters.m_pointLightSpecular[1] = vec3(2.0f, 2.0f, 0.3f) * flashIntensity;
		renderParameters.m_pointLightRange[1] = 8.0f * flashIntensity;
		renderParameters.m_pointLightFalloff[1] = 2.0f * flashIntensity;

		// Flickering Torch
		renderParameters.m_pointLightRange[0] = 11.0f + 2.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f ;
		renderParameters.m_pointLightFalloff[0] = 0.0f + 1.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f;

		//Render();
	}

	// This is just for testing until you get this incorportated into GameManager
}

vec3 GameManager::monsColDirection(Monster* m, Object* o)
{
	vec3* M = m->getPosition();
	vec3* T = o->getPosition();
	vec3* P = m_player->getPosition();

	double r = (M->z-T->z)*(M->z-P->z)-(M->x-T->x)*(P->x-M->x);
	r = r / (length(*M-*P)*length(*M-*P));
	vec3 X = vec3(M->x+r*(P->x-M->x),0, M->z+r*(P->z-M->z));
	vec3 V = normalize(normal(X-*T));
	vec3 nT = normalize(normal(*M-*T));
	vec3 PM = normalize(*P-*M);
	V = vec3((int)(V.x*1000), 0.0, (int)(V.z*1000));
	PM = vec3((int)(PM.x*1000), 0.0, (int)(PM.z*1000));

	if(PM == V)
		return nT;
	else
		return -nT;
}

void GameManager::RenderHUD()
{
	SetCameraOrthogonal();

	float score_position = 9.4;
	int temp = m_score;

	// Render each score number in upper right corner
	do {
		RenderBatch* batch = new RenderBatch();

		batch->m_geometryID = intID(temp%10);
		batch->m_effectParameters.m_materialAmbient = vec3(5.0f, 5.0f, 5.0f);
		batch->m_effectParameters.m_materialDiffuse = vec3(0.0f, 0.0f, 0.0f);
		batch->m_effectParameters.m_materialSpecular = vec3(0.0f, 0.0f, 0.0f);
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.0f;
		batch->m_effectParameters.m_materialOpacity = 0.9999f;
		batch->m_effectParameters.m_diffuseTexture = "numbers";	
		batch->m_effectParameters.m_normalMap = "none";
		batch->m_effectParameters.m_HUDRender = true;
		batch->m_effectParameters.m_materialOpacity = 1.0f;
		batch->m_effectParameters.m_modelviewMatrix = Translate(score_position, 9.0, 0.0);

		m_graphicsManager->Render(*batch);

		temp /= 10;
		score_position -= 0.6;

		delete batch;

	} while(temp != 0);

	// Render lives in upper right corner (now only supports single digits)
	temp = m_player->getLives();

	RenderBatch* rb = new RenderBatch();
	rb->m_geometryID = intID(temp);
	rb->m_effectParameters.m_materialAmbient = vec3(5.0f, 5.0f, 5.0f);
	rb->m_effectParameters.m_materialDiffuse = vec3(0.0f, 0.0f, 0.0f);
	rb->m_effectParameters.m_materialSpecular = vec3(0.0f, 0.0f, 0.0f);
	rb->m_effectParameters.m_materialSpecularExponent = 1.0f;
	rb->m_effectParameters.m_materialGloss = 0.0f;
	rb->m_effectParameters.m_materialOpacity = 0.9999f;
	rb->m_effectParameters.m_diffuseTexture = "numbers";	
	rb->m_effectParameters.m_normalMap = "none";
	rb->m_effectParameters.m_HUDRender = true;
	rb->m_effectParameters.m_materialOpacity = 1.0f;
	rb->m_effectParameters.m_modelviewMatrix = Translate(-10.0, 9.0, 0.0);

	m_graphicsManager->Render(*rb);

	delete rb;

	// Render game over 
	if (m_pause) {
		RenderBatch* rb = new RenderBatch();
		rb->m_geometryID = "gameover";
		rb->m_effectParameters.m_materialAmbient = vec3(5.0f, 5.0f, 5.0f);
		rb->m_effectParameters.m_materialDiffuse = vec3(0.0f, 0.0f, 0.0f);
		rb->m_effectParameters.m_materialSpecular = vec3(0.0f, 0.0f, 0.0f);
		rb->m_effectParameters.m_materialSpecularExponent = 1.0f;
		rb->m_effectParameters.m_materialGloss = 0.0f;
		rb->m_effectParameters.m_materialOpacity = 0.9999f;
		rb->m_effectParameters.m_diffuseTexture = "gameover";	
		rb->m_effectParameters.m_normalMap = "none";
		rb->m_effectParameters.m_HUDRender = true;
		rb->m_effectParameters.m_materialOpacity = 1.0f;
		rb->m_effectParameters.m_modelviewMatrix = mat4();

		m_graphicsManager->Render(*rb);

		delete rb;
	}


	SetupCamera(m_pp);
}

std::string GameManager::intID(int x)
{
	switch(x) {
	case 1: return "one"; break;
	case 2: return "two"; break;
	case 3: return "three"; break;
	case 4: return "four"; break;
	case 5: return "five"; break;
	case 6: return "six"; break;
	case 7: return "seven"; break;
	case 8: return "eight"; break;
	case 9: return "nine"; break;
	case 0: return "zero"; break;
	default: return "none";
	}
}

directionType relativePosition(Object& a, Object& b)
{
	vec3* op = b.getPosition();
	vec3* pp = a.getPosition();
	if(op->x <= pp->x)
		if((op->z <= (pp->z + (pp->x - op->x))) && (op->z >= (pp->z - (pp->x - op->x))))
			return LEFT;
	if(op->x > pp->x)
		if((op->z <= (pp->z + (op->x - pp->x))) && (op->z >= (pp->z - (op->x - pp->x))))
			return RIGHT;
	if(op->z <= pp->z)
		if((op->x <= (pp->x + (pp->z - op->z))) && (op->x >= (pp->x - (pp->z - op->z))))
			return UP;
	if(op->z > pp->z)
		if((op->x <= (pp->x + (op->z - pp->z))) && (op->x >= (pp->x - (op->z - pp->z))))
			return DOWN;
}


void GameManager::renderBG()
{
	int s = 0;
	int e = 15;
	GLfloat p = m_pp.x;

	if(p >= -375)	s = 0;		if(p < 375)		e = 15;
	if(p >= -325)	s = 1;		if(p < 325)		e = 14;
	if(p >= -275)	s = 2;		if(p < 275)		e = 13;
	if(p >= -225)	s = 3;		if(p < 225)		e = 12;
	if(p >= -175)	s = 4;		if(p < 175)		e = 11;
	if(p >= -125)	s = 5;		if(p < 125)		e = 10;
	if(p >= -75)	s = 6;		if(p < 75)		e = 9;
	if(p >= -25)	s = 7;		if(p < 25)		e = 8;
	if(p >= 25)		s = 8;		if(p < -25)		e = 7;
	if(p >= 75)		s = 9;		if(p < -75)		e = 6;
	if(p >= 125)	s = 10;		if(p < -125)	e = 5;
	if(p >= 175)	s = 11;		if(p < -175)	e = 4;
	if(p >= 225)	s = 12;		if(p < -225)	e = 3;
	if(p >= 275)	s = 13;		if(p < -275)	e = 2;
	if(p >= 325)	s = 14;		if(p < -325)	e = 1;
	if(p >= 375)	s = 15;		if(p < -375)	e = 0;

	s *= 500;	e = (1 + e) * 500;

	for(int i = s; i < e; i++)
		if(length(*m_bgenviro.at(i)->getPosition()-m_pp) <= 50)
			m_graphicsManager->Render(*m_bgenviro.at(i)->getRenderBatch());

	for(int i = 8000; i < m_bgenviro.size(); i++)
		if(length(*m_bgenviro.at(i)->getPosition()-m_pp) <= 50)
			m_graphicsManager->Render(*m_bgenviro.at(i)->getRenderBatch());
}


void GameManager::spawnMonsters()
{
	srand((unsigned)time(0));
	directionType dir = directions[rand()%8];
	vec3 anchor;
	switch(dir)
	{
	case UP:		anchor = vec3(0,0,-1);	break;
	case DOWN:		anchor = vec3(0,0,1);	break;
	case LEFT:		anchor = vec3(-1,0,0);	break;
	case RIGHT:		anchor = vec3(1,0,0);	break;
	case UPLEFT:	anchor = vec3(-1,0,-1);	break;
	case UPRIGHT:	anchor = vec3(1,0,-1);	break;
	case DOWNLEFT:	anchor = vec3(-1,0,1);	break;
	case DOWNRIGHT:	anchor = vec3(1,0,1);	break;
	}

	vec3 an = normal(anchor);
	vec3 position;
	for(int i=0;i<5;i++)
	{
		position = m_pp + 15*anchor + anchor*(rand()%5) + (20-rand()%40)*an;
		Spawn(MONSTER,position,0.8);
	}
}