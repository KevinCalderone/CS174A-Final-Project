#ifndef __RENDERPARAMETERS_H__
#define __RENDERPARAMETERS_H__

#include "Angel.h"

struct RenderParameters
{
	// Camera Parameters
	mat4 m_projectionMatrix;
	vec3 m_eyePosition;

	// Global Light Parameters
	vec3 m_lightDirection;
	vec3 m_lightAmbient;
	vec3 m_lightDiffuse;
	vec3 m_lightSpecular;
};

#endif