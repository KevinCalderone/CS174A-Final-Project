#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "../Code/Angel.h"
#include "../Code/GraphicsManager.h"
#include "../Code/Object.h"
#include "../Code/Player.h"
#include "../Code/Monster.h"
#include "../Code/Bullet.h"
#include "../Code/EnviroObj.h"
#include "../Code/Ground.h"
#include <vector>

const enum objectType {PLAYER, MONSTER, BULLET, BUSH};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void initGame();
	void callbackKeyboard (unsigned char key, int x, int y);
	GraphicsManager* getGraphicsManager(); // temporary?
private:
	Player* m_player;
	std::vector<Monster*> m_monsters;
	std::vector<Bullet*> m_bullets;
	std::vector<EnviroObj*> m_enviro;
	Ground* m_ground;
	GraphicsManager* m_graphicsManager;
	int m_score;
	const int MONSTERCAP;
	bool Spawn(objectType type, vec3 position, double size=10.0, bool permit=true);
	void Delete(Object* object);
	void Update();
	void CollisionDetection();
	void Render();
	void initPlayer();
	void initMonsters();
	void initEnviro();
};

#endif