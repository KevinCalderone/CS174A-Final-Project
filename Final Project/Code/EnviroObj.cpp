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
		batch->m_effectParameters.m_twoSided = true;
		batch->m_effectParameters.m_diffuseTexture = "leaves";	
		batch->m_effectParameters.m_normalMap = "none";
		batch->m_effectParameters.m_materialOpacity = 0.3f;
	}
	if(type==ROCK)
	{
		batch->m_geometryID = "rock";
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 1.0f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.1f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.1f;
		batch->m_effectParameters.m_materialSpecularExponent = 14.0f;
		batch->m_effectParameters.m_materialGloss = 0.01f;
		batch->m_effectParameters.m_diffuseTexture = "rock";	
		batch->m_effectParameters.m_normalMap = "rockNormal";

		m_bbfactor = 85.0;
	}
	if(type==BUSH)
	{
		const unsigned int c_num_plants = 5;
		const char* plantTypes[c_num_plants] = 
		{
			"smallBush",
			"fern",
			"fern2",
			"fern3",
			"fern4"
		};

		int type = rand() % c_num_plants;

		batch->m_geometryID = plantTypes[type];
		batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 0.0f) * 0.5f;
		batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 0.0f) * 0.3f;
		batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.8f, 0.0f) * 0.0f;
		batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
		batch->m_effectParameters.m_materialGloss = 0.1f;
		batch->m_effectParameters.m_twoSided = true;
		batch->m_effectParameters.m_diffuseTexture = plantTypes[type];	
		batch->m_effectParameters.m_normalMap = "none";
		batch->m_effectParameters.m_materialOpacity = 1.0f;
	}
	this->setRenderBatch(batch);

	m_bb = new BoundingBox(vec2(position.x,position.z),m_bbfactor*size,m_bbfactor*size);
}

EnviroObj::~EnviroObj() {
}