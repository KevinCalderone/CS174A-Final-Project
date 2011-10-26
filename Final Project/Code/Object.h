#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <list>

#include "ShaderState.h"
#include "Vertex.h"

class Object
{
public:
	Object (Object* parent);
	~Object ();

	void UpdateTree (float delta);
	void RenderTree ();

	unsigned int LoadTreeData (unsigned int bufferOffset);
	unsigned int GetTreeDataSize () const;

	mat4 GetWorldTransform ();

	// Render Options
	void SetPosition (const vec3& position) { m_position = position; }
	void SetAngularVelocity (const vec3& angularVelocity) { m_angularVelocity = angularVelocity; }
	void SetScale (float scale) { m_scale = scale; }

	void SetVertexLighting (bool vertexLighting) { m_state.m_vertexLighting = vertexLighting; }
	void SetAmbientColor (vec3 ambientColor) { m_state.m_ambientColor = ambientColor; }
	void SetAmbientCoefficient (float ambientCoefficient) { m_state.m_ambientCoefficient = ambientCoefficient; }
	void SetDiffuseColor (vec3 diffuseColor) { m_state.m_diffuseColor = diffuseColor; }
	void SetDiffuseCoefficient (float diffuseCoefficient) { m_state.m_diffuseCoefficient = diffuseCoefficient; }
	void SetSpecularColor (vec3 specularColor) { m_state.m_specularColor = specularColor; }
	void SetSpecularCoefficient (float specularCoefficient) { m_state.m_specularCoefficient = specularCoefficient; }
	void SetSpeculatExponent (float specularExponent) { m_state.m_specularExponent = specularExponent; }

protected:
	void AllocateVertexData (unsigned int count);

	unsigned int m_bufferOffset;
	unsigned int m_vertexCount;
	Vertex* m_data;
	ShaderState m_state;

private:
	void DetachFromParent () { m_parent = NULL; }
	void AddChild (Object* object);
	void RemoveChild (Object* object);

	vec3 m_position;
	vec3 m_rotation;
	float m_scale;

	vec3 m_velocity;
	vec3 m_angularVelocity;

    Object* m_parent;
	std::list<Object*> m_children;
};

#endif