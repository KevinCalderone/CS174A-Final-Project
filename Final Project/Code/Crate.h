#ifndef __CRATE_H__
#define __CRATE_H__

#include "Object.h"

class Crate : public Object
{

public:
	Crate(objectType type, vec3 position, vec3 direction, float size);
	~Crate();
	void Update(float delta);
//private:
	//float m_theta;
};


#endif