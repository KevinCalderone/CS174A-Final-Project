#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Vertex.h"
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

	void AllocateVertexData (unsigned int count);

	unsigned int m_vertexCount;

	Vertex* m_data;
	ShaderState m_state;
	RenderBatch m_render;

private:
	vec3 m_position;
	vec3 m_direction;
	float m_scale;

	vec3 m_velocity;
};


#endif