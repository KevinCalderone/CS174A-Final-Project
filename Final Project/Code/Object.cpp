#include "Object.h"




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
}

void Object::setVelocity (const vec3& velocity) {
	m_velocity = velocity;
}

void Object::setDirection (const vec3& direction) {
	m_direction = direction;
}

void Object::setSize (float size) {
	m_size = size;
}

void Object::setRenderBatch(RenderBatch* rb) {
	m_render = rb;
}

vec3* Object::getPosition () {
	return &m_position;
}

vec3* Object::getDirection () {
	return &m_direction;
}

RenderBatch* Object::getRenderBatch () {
	return m_render;
}

void Object::Update(float delta) {
}