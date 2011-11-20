#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "RenderBatch.h"
#include "BoundingBox.h"

const enum objectType {PLAYER, MONSTER, BULLET, TREE, LEAVES, ROCK, BUSH};

class Object
{

public:
	Object ();
	Object (vec3 position);
	Object (vec3 position, vec3 velocity, float size, float speed);
	~Object ();

	void setPosition (const vec3& position);
	void setVelocity (const vec3& velocity);
	void setSize (float size);
	void setSpeed (float speed);
	void setRenderBatch(RenderBatch* rb);

	vec3* getVelocity();

	BoundingBox* getBoundingBox();
	vec3* getPosition ();
	RenderBatch* getRenderBatch ();

	void Update(float delta);

protected:
	BoundingBox* m_bb;
	RenderBatch* m_render;
	vec3 m_position;
	vec3 m_velocity;
	float m_size;
	float m_speed;
	float m_bbfactor;

	
};


#endif