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
#include "Crate.h"
#include "Timer.h"
#include <vector>
#include "FMOD\fmod.hpp"
#include "FMOD\fmod_errors.h"

const enum directionType {UP,DOWN,LEFT,RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
const directionType directions[8] = {UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
const enum soundType {MACHINEGUN, SHOTGUN, MONSDEATH, BGMUSIC, GRUNT, GLOAD};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void initGame();
	void Render();
	void callbackKeyboard (unsigned char key, int x, int y);
	void callbackKeyUp (unsigned char key, int x, int y);
private:
	Player* m_player;
	vec3 m_pp;
	vec3 m_pgp;
	float m_flashTimer;
	float m_timeOfDay;
	std::vector<Monster*> m_monsters;
	std::vector<Bullet*> m_bullets;
	std::vector<EnviroObj*> m_enviro;
	std::vector<EnviroObj*> m_bgenviro;
	std::vector<Crate*> m_powerups;
	std::vector<Crate*> m_walls;
	Ground* m_ground;
	GraphicsManager* m_graphicsManager;
	int m_score;
	int m_god;
	bool m_godmode;
	static const int MONSTERCAP = 10;
	void Spawn(objectType type, vec3& position, float size=10.0);
	void spawnMonsters();
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
	void initParameters();
	void renderBG();
	void SetCameraOrthogonal();
	void SetupCamera(vec4 playerPos);
	void updateCamera();
	void updateLighting();
	vec3 monsColDirection(Monster* m, Object* o);
	void playSound(soundType sound);
	FMOD::System *m_system;
    FMOD::Sound *m_sounds[6];
    FMOD::Channel *m_bulletchannel;
	FMOD::Channel *m_monschannel;
	FMOD::Channel *m_bgchannel;
	FMOD::Channel *m_fxchannel;
	bool m_mute;

	void RenderHUD();
	std::string intID(int x);

	void ResetGame();
	bool m_pause;

	Timer* m_timer;
	float m_delta;
};

directionType relativePosition(Object& a, Object& b);

#endif