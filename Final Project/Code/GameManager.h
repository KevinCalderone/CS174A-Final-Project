#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Angel.h"
#include "GraphicsManager.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "EnviroObj.h"
#include "Ground.h"
#include <vector>
#include "FMOD\fmod.hpp"
#include "FMOD\fmod_errors.h"

const enum directionType {UP,DOWN,LEFT,RIGHT};
const enum soundType {MACHINEGUN, SHOTGUN, MONSDEATH, BGMUSIC};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void initGame();
	void Render();
	void callbackKeyboard (unsigned char key, int x, int y);
	void callbackKeyUp (unsigned char key, int x, int y);
	GraphicsManager* getGraphicsManager(); // temporary?
	Player* getPlayer();
private:
	Player* m_player;
	std::vector<Monster*> m_monsters;
	std::vector<Bullet*> m_bullets;
	std::vector<EnviroObj*> m_enviro;
	std::vector<EnviroObj*> m_bgenviro;
	Ground* m_ground;
	GraphicsManager* m_graphicsManager;
	int m_score;
	int m_god;
	bool m_godmode;
	static const int MONSTERCAP = 1;
	void Spawn(objectType type, vec3 position, float size=10.0);
	Monster* spawnMonster();
	Player* spawnPlayer();
	Bullet* spawnBullet(vec3 position);
	float angle;
	bool m_w,m_a,m_s,m_d,m_j,m_l,m_auto;
	void Delete(objectType type, int index=0);
	void Update();
	void keyboardUpdate();
	void CollisionDetection();
	void initSounds();
	void initPlayer();
	void initMonsters();
	void initEnviro();
	void SetCameraOrthogonal();
	void SetupCamera(vec4 playerPos);
	void updateCamera();
	vec3 monsColDirection(Monster* m, EnviroObj* e);
	void playSound(soundType sound);
	FMOD::System *m_system;
    FMOD::Sound *m_sounds[4];
    FMOD::Channel *m_bulletchannel;
	FMOD::Channel *m_monschannel;
	FMOD::Channel *m_bgchannel;
};

directionType relativePosition(Object& a, Object& b);

#endif