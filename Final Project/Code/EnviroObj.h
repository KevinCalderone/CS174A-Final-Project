#ifndef __ENVIROOBJ_H__
#define __ENVIROOBJ_H__

#include "Object.h"

class EnviroObj : public Object
{

public:
	EnviroObj(objectType type, vec3 position, vec3 direction, float size);
	~EnviroObj();
};


#endif