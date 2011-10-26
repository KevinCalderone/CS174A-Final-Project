#include "Object.h"

class DebugObject : public Object
{
public:
	DebugObject (Object* parent) : Object(parent) {
		
		AllocateVertexData(3);

		m_data[0].position.x = -1.0f;
		m_data[0].position.y = -1.0f;
		m_data[0].position.z = 1.0f;
		m_data[0].normal.x = 1.0f;
		m_data[0].normal.y = 0.0f;
		m_data[0].normal.z = 0.0f;

		m_data[1].position.x = -1.0f;
		m_data[1].position.y = 1.0f;
		m_data[1].position.z = 1.0f;
		m_data[1].normal.x = 0.0f;
		m_data[1].normal.y = 1.0f;
		m_data[1].normal.z = 0.0f;

		m_data[2].position.x = 1.0f;
		m_data[2].position.y = 1.0f;
		m_data[2].position.z = 1.0f;
		m_data[2].normal.x = 0.0f;
		m_data[2].normal.y = 0.0f;
		m_data[2].normal.z = 1.0f;

		m_state.m_ambientColor = vec3(1.0f, 0.0f, 0.0f);
	}

private:

};