#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(vec3 position, vec3 velocity, float size, float speed)
	: Object(position, velocity, size, speed)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "monster";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 0.1f;
	batch->m_effectParameters.m_diffuseTexture = "monster";	
	batch->m_effectParameters.m_normalMap = "monsterNormal";
	batch->m_effectParameters.m_animationTime = (rand()%10000) / 100.0f;
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),0.8*size,1.2*size);//1.2
}

void Monster::setVelocity(const vec3& velocity)
{
	m_bb->setDirection(vec2(velocity.x,velocity.z));
	m_velocity = velocity * m_speed;
}

float Monster::getSize()
{
	return m_size;
}