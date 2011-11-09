#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"

class Player : public Object
{

public:
	Player ();
	~Player ();

	bool shoot();
	bool kill();

	void setDirection (const vec3& direction);
	vec3* getDirection ();
	vec3* getVelocity ();
	void setWeaponDelay(int delay);
	void addLife(int add);
	void removeLife();
	void Update(float delta);


private:

	int m_lives;
	int m_weaponDelay;
	int m_cooldown;
	vec3 m_direction;
};


#endif