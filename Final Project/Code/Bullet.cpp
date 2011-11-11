#include "Bullet.h"

Bullet::Bullet(vec3 position)
	: Object(position)
{
}

Bullet::Bullet(vec3 position, vec3 velocity, float size, float speed)
	: Object(position, velocity, size, speed)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "sphere";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 100.f;
	batch->m_effectParameters.m_diffuseTexture = "panda";	
	batch->m_effectParameters.m_normalMap = "monsterNormal";
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),1*size,1*size);
}