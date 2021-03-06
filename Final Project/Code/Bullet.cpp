#include "Bullet.h"

Bullet::Bullet(vec3 position)
	: Object(position)
{
}

Bullet::Bullet(vec3 position, vec3 velocity, float size, float speed)
	: Object(position, velocity, size, speed)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "bullet";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 30.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 5.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.8f) * 0.1f;
	batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
	batch->m_effectParameters.m_materialGloss = 0.0f;
	batch->m_effectParameters.m_diffuseTexture = "monster";	
	batch->m_effectParameters.m_normalMap = "none";
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),1*size,1*size);
}