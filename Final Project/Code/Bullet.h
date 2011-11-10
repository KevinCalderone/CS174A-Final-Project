#ifndef __BULLET_H__
#define __BULLET_H__

#include "Object.h"

class Bullet : public Object
{
public:
	Bullet(vec3 position);
	Bullet(vec3 position, vec3 velocity, float size, float speed);
};


#endif