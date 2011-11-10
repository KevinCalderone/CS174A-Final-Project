#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Object.h"

class Monster : public Object
{

public:
	Monster();
	Monster(vec3 position, vec3 velocity, float size, float speed);
	~Monster();
};


#endif