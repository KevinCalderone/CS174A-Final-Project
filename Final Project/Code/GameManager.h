#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Angel.h"
#include "ShaderState.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "EnviroObj.h"
#include "Ground.h"
#include <vector>

const enum objectType {player, monster, bullet, bush};

class GameManager
{
public:
	GameManager(){};
	~GameManager();
	static void initGame();
private:
	Player* m_player;
	std::vector<Monster*> m_monsters;
	std::vector<Bullet*> m_bullets;
	std::vector<EnviroObj*> m_enviro;
	Ground* m_ground;
	ShaderState* m_shaderstate;
	int m_score;

	void Spawn(objectType type, vec3 position, double size=10.0, bool permit=true);
	void Delete(Object* object);
	void callbackKeyboard (unsigned char key, int x, int y);
	void Update();
	void CollisionDetection();
	void Render();
};

#endif