#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include "Angel.h"

typedef bool static_branch;

class ShaderState 
{
public:
	ShaderState () {};

	void Apply ();

	static vec3 m_eyePosition;
	static vec3 m_lightPosition;
	
	static mat4 m_viewportMatrix;
	mat4 m_modelviewMatrix;

	static_branch m_vertexLighting;

	vec3 m_ambientColor;
	float m_ambientCoefficient;
	vec3 m_diffuseColor;
	float m_diffuseCoefficient;
	vec3 m_specularColor;
	float m_specularCoefficient;
	float m_specularExponent;

	// Static Statemachine Shader State
	static void InitShaders ();

	static GLuint s_program;
	static GLuint s_buffer;

	static GLuint a_vPosition;
	static GLuint a_vNormal;

	static GLuint u_eyePosition;
	static GLuint u_lightPosition;

	static GLuint u_viewportMatrix;
	static GLuint u_modelviewMatrix;

	static GLuint u_vertexLighting;

	static GLuint u_ambientColor;
	static GLuint u_ambientCoefficient;
	static GLuint u_diffuseColor;
	static GLuint u_diffuseCoefficient;
	static GLuint u_specularColor;
	static GLuint u_specularCoefficient;
	static GLuint u_specularExponent;
};

#endif