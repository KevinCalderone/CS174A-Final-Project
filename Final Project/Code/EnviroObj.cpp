#include "EnviroObj.h"

EnviroObj::EnviroObj(objectType type, vec3 position, vec3 direction, float size)
	: Object(position, direction, size, 0.f)
{
	RenderBatch* batch = new RenderBatch();
	if(type==TREE)
	{
		batch->m_geometryID = "cone";
		batch->m_effectParameters.m_materialAmbient = vec3(0.0f, 1.0f, 0.0f) * 5.0f;
		batch->m_effectParameters.m_materialDiffuse = vec3(0.0f, 1.0f, 0.0f) * 5.0f;
		batch->m_effectParameters.m_materialSpecular = vec3(0.5f, 1.0f, 0.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.1f;
		batch->m_effectParameters.m_diffuseTexture = "none";	
		batch->m_effectParameters.m_normalMap = "none";
	}
	if(type==ROCK)
	{
		batch->m_geometryID = "cube";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 0.0f) * 5.0f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 0.0f) * 5.0f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.1f;
		batch->m_effectParameters.m_diffuseTexture = "none";	
		batch->m_effectParameters.m_normalMap = "none";
	}
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),1*size,1*size);
}

EnviroObj::~EnviroObj() {
}