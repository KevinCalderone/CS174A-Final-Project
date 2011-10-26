#include "Object.h"

Object::Object (Object* parent) 
	: m_parent(parent), m_data(NULL), m_vertexCount(0), m_scale(1.0f)
{
	if (m_parent != NULL)
		m_parent->AddChild(this);
}

Object::~Object () {
	if (m_data)
		delete m_data;

	for (std::list<Object*>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter) {
		(*iter)->DetachFromParent();
		delete (*iter);
	}

	if (m_parent != NULL)
		m_parent->RemoveChild(this);
}

void Object::UpdateTree (float delta) {
	m_position += delta * m_velocity;
	m_rotation += delta * m_angularVelocity;

	for (std::list<Object*>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
		(*iter)->UpdateTree(delta);
}

void Object::RenderTree () {
	if (m_data != NULL) {
		m_state.m_modelviewMatrix = GetWorldTransform();
		m_state.Apply();

		glDrawArrays(GL_TRIANGLES, m_bufferOffset, m_vertexCount);
	}

	for (std::list<Object*>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
		(*iter)->RenderTree();
}

unsigned int Object::LoadTreeData (unsigned int bufferOffset) {
	unsigned int bufferEnd = bufferOffset;

	if (m_data != NULL) {
		unsigned int dataSize = m_vertexCount * sizeof(Vertex);
		unsigned int offsetSize = bufferOffset * sizeof(Vertex);
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, dataSize, &m_data[0]);
		m_bufferOffset = bufferOffset;
		bufferEnd += m_vertexCount;
	}

	for (std::list<Object*>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter) {
		bufferEnd =(*iter)->LoadTreeData(bufferEnd);
	}

	return bufferEnd;
}

unsigned int Object::GetTreeDataSize () const {
	unsigned int totalData = m_vertexCount * sizeof(Vertex);

	for (std::list<Object*>::const_iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
		totalData += (*iter)->GetTreeDataSize();

	return totalData;
}

mat4 Object::GetWorldTransform () {
	mat4 localTransform = Angel::Translate(m_position) * 
						  Angel::Scale(m_scale, m_scale, m_scale) *
		                  Angel::RotateX(m_rotation.x) * 
		                  Angel::RotateY(m_rotation.y) * 
		                  Angel::RotateZ(m_rotation.z);

	if (m_parent != NULL)
		return m_parent->GetWorldTransform() * localTransform;
	else
		return localTransform;
}

void Object::AllocateVertexData (unsigned int count) {
	if (m_data != NULL)
		delete m_data;

	m_vertexCount = count;
	m_data = new Vertex[m_vertexCount];
}

void Object::AddChild (Object* object) {
	m_children.push_back(object);
}

void Object::RemoveChild (Object* object) {
	m_children.remove(object);
}
