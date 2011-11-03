#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "RenderBatch.h"

class Object
{

public:

	void setPosition (const vec3& position);
	void setVelocity (const vec3& velocity);
	void setDirection (const vec3& direction);
	void setScale (float scale);

	vec3* getPosition ();
	vec3* getDirection ();
	ShaderState* getShaderState ();
	RenderBatch* getRenderBatch ();

	void Update(float delta);
	void Render();

protected:

	RenderBatch m_render;

private:
	vec3 m_position;
	vec3 m_direction;
	float m_scale;

	vec3 m_velocity;
};


#endif