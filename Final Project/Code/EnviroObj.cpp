#include "EnviroObj.h"

EnviroObj::EnviroObj(objectType type, vec3 position, vec3 direction, float size)
	: Object(position, direction, size, 0.f)
{
	RenderBatch* batch = new RenderBatch();
	if(type==TREE)
	{
		batch->m_geometryID = "tree";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.3f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.0f;
		batch->m_effectParameters.m_diffuseTexture = "tree";	
		batch->m_effectParameters.m_normalMap = "none";

		m_bbfactor = 0.6;
	}
	if(type==LEAVES) 
	{
		batch->m_geometryID = "leaves";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.3f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.0f;
		batch->m_effectParameters.m_diffuseTexture = "leaves";	
		batch->m_effectParameters.m_normalMap = "none";
		batch->m_effectParameters.m_materialOpacity = 0.3f;
	}
	if(type==ROCK)
	{
		batch->m_geometryID = "cube";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 0.0f) * 0.5f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 0.0f) * 0.3f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.1f;
		batch->m_effectParameters.m_diffuseTexture = "none";	
		batch->m_effectParameters.m_normalMap = "none";
	}
	if(type==BUSH)
	{
		batch->m_geometryID = "bush";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 0.0f) * 0.5f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 0.0f) * 0.3f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.1f;
		batch->m_effectParameters.m_diffuseTexture = "bush";	
		batch->m_effectParameters.m_normalMap = "none";
		batch->m_effectParameters.m_materialOpacity = 0.7f;
	}
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),m_bbfactor*size,m_bbfactor*size);
}

EnviroObj::~EnviroObj() {
}