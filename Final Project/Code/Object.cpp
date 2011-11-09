#include "Object.h"

const GLfloat R2D = 180.0f/(atan(1.0f)*4.0f);


Object::Object ()
	: m_render(NULL)
{
}

Object::~Object () {
	if(m_render != NULL)
		delete m_render;
}

void Object::setPosition (const vec3& position) {
	m_position = position;
	//if(m_render!=NULL)
	//	m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
	//													* Angel::RotateY((GLfloat)90+atan2(m_velocity.x,m_velocity.z)*R2D);
}

void Object::setVelocity (const vec3& velocity) {
	m_velocity = velocity * m_speed;
	//if(m_render!=NULL)
	//	m_render->m_effectParameters.m_modelviewMatrix *= Angel::RotateY((GLfloat)90+atan2(velocity.x,velocity.z)*R2D);
}

void Object::setSize (float size) {
	m_size = size;
}

void Object::setSpeed(float speed) {
	m_speed = speed;
}

void Object::setRenderBatch(RenderBatch* rb) {
	m_render = rb;
}

vec3* Object::getPosition () {
	return &m_position;
}

RenderBatch* Object::getRenderBatch () {
	return m_render;
}

void Object::Update(float delta) {
	if(m_render!=NULL)
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
														* Angel::RotateY((GLfloat)90+atan2(m_velocity.x,m_velocity.z)*R2D);
}