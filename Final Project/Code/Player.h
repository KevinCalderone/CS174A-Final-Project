#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"

class Player : public Object
{

public:
	Player ();
	~Player ();

	bool shoot();
	void kill();

	void setWeaponDelay(int delay);
	void setCooldown(int cooldown);
	void addLife(int add);
	void removeLife();


private:

	int m_lives;
	int m_weaponDelay;
	int m_cooldown;
};


#endif