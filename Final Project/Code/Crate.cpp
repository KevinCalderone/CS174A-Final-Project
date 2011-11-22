#include "Crate.h"

Crate::Crate(objectType type, vec3 position, vec3 direction, float size)
	: Object(position, direction, size, 1.f)
{
	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "cube";
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f) * 0.5f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f) * 0.3f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.0f;
	batch->m_effectParameters.m_materialSpecularExponent = 1.0f;
	batch->m_effectParameters.m_materialGloss = 0.0f;
	batch->m_effectParameters.m_diffuseTexture = "rock";	
	batch->m_effectParameters.m_normalMap = "none";

	this->setRenderBatch(batch);
}

Crate::~Crate() {
}

void Crate::Update(float delta)
{
	float theta = 3 * delta * DegreesToRadians;
	m_velocity.x = m_velocity.x*cos(theta)-m_velocity.z*sin(theta);
	m_velocity.z = m_velocity.x*sin(theta)+m_velocity.z*cos(theta);

	if(m_render!=NULL) {
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
														* Angel::RotateY((GLfloat)180+atan2(m_velocity.x,m_velocity.z)/DegreesToRadians);
		m_render->m_effectParameters.m_animationTime += delta * 0.2f;
	}
}