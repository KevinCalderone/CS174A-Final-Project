#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"

enum gunType {UZI, SHOTTY};

class Player : public Object
{

public:
	Player ();
	Player (vec3 position, vec3 direction, float size, float speed, int lives, float weaponDelay);
	~Player ();

	bool shoot(float delta);
	bool kill();

	void setDirection (const vec3& direction);
	vec3* getDirection ();
	vec3* getVelocity ();
	void setVelocity(const vec3& velocity);
	void setWeaponDelay(float delay);
	void addLife(int add);
	void removeLife();
	void Update(float delta);
	void setWeapon(gunType gun);
	gunType getWeapon();
	int getLives();


private:

	gunType m_gun;
	int m_ammo;
	int m_lives;
	float m_weaponDelay;
	float m_cooldown;
	vec3 m_direction;
};


#endif