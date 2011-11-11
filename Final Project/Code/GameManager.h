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

const enum objectType {PLAYER, MONSTER, BULLET, BUSH};

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
	Ground* m_ground;
	GraphicsManager* m_graphicsManager;
	int m_score;
	static const int MONSTERCAP = 50;
	void Spawn(objectType type, vec3 position, double size=10.0);
	Monster* spawnMonster();
	Player* spawnPlayer();
	Bullet* spawnBullet(vec3 position);
	float angle;
	bool m_w,m_a,m_s,m_d,m_j,m_l,m_auto;
	void Delete(objectType type, int index=0);
	void Update();
	void keyboardUpdate();
	void CollisionDetection();
	void initPlayer();
	void initMonsters();
	void initEnviro();
};

#endif