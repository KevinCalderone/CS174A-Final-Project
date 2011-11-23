#include "Ground.h"

Ground::Ground() 
	: m_render(NULL)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "plane";	
	batch->m_effectParameters.m_modelviewMatrix =  mat4();
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 2.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(0.0f, 0.0f, 1.0f) * 0.3f;
	batch->m_effectParameters.m_materialSpecularExponent = 6.0f;
	batch->m_effectParameters.m_materialGloss = 0.0f;
	batch->m_effectParameters.m_diffuseTexture = "grass";	
	batch->m_effectParameters.m_normalMap = "grassNormal";
	this->setRenderBatch(batch);
}

Ground::~Ground() {
	if (m_render != NULL)
		delete m_render;
}

void Ground::setRenderBatch(RenderBatch* rb) {
	m_render = rb;
}

RenderBatch* Ground::getRenderBatch () {
	return m_render;
}