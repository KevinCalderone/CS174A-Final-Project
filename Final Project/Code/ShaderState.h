#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include "mat.h"

typedef bool static_branch;

struct ShaderState
{
	mat4 m_projectionMatrix;
	mat4 m_modelviewMatrix;

	static_branch b_useTexture0;

	vec3 m_eyePosition;

	vec3 m_lightDirection;
	vec3 m_lightCombinedAmbient;
	vec3 m_lightCombinedDiffuse;
	vec3 m_lightCombinedSpecular;
	float m_materialSpecularExponent;
};

#endif