#include "Object.h"


Object::Object()
	: m_render(NULL), m_bb(NULL)
{
}

Object::Object (vec3 position)
	: m_render(NULL), m_position(position)
{
}

Object::Object (vec3 position, vec3 velocity, float size, float speed)
	: m_position(position), m_velocity(velocity), m_size(size), m_speed(speed)
{
}

Object::~Object () {
	if(m_render != NULL)
		delete m_render;
}

void Object::setPosition (const vec3& position) {
	m_position = position;
	m_bb->setCenter(vec2(m_position.x,m_position.z));
	//if(m_render!=NULL)
	//	m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
	//													* Angel::RotateY((GLfloat)90+atan2(m_velocity.x,m_velocity.z)*R2D);
}

void Object::setVelocity (const vec3& velocity) {
	m_velocity = velocity * m_speed;
	//if(m_render!=NULL)
	//	m_render->m_effectParameters.m_modelviewMatrix *= Angel::RotateY((GLfloat)90+atan2(velocity.x,velocity.z)*R2D);
}

vec3* Object::getVelocity() {
	return &m_velocity;
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

BoundingBox* Object::getBoundingBox()
{
	return m_bb;
}

vec3* Object::getPosition () {
	return &m_position;
}

RenderBatch* Object::getRenderBatch () {
	return m_render;
}

void Object::Update(float delta) {
	m_position += m_velocity;
	m_bb->setCenter(vec2(m_position.x,m_position.z));
	if(m_render!=NULL)
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(m_position) * Angel::Scale(vec3(m_size))
														* Angel::RotateY((GLfloat)90+atan2(m_velocity.x,m_velocity.z)/DegreesToRadians);
}