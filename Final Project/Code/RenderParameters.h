#ifndef __RENDERPARAMETERS_H__
#define __RENDERPARAMETERS_H__

#include "Angel.h"

#include "GraphicsSettings.h"

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
	std::string m_environmentMap;

	// Point Light Parameters
	vec3 m_pointLightPosition[c_num_point_lights];
	vec3 m_pointLightAmbient[c_num_point_lights];
	vec3 m_pointLightDiffuse[c_num_point_lights];
	vec3 m_pointLightSpecular[c_num_point_lights];
	float m_pointLightRange[c_num_point_lights];
	float m_pointLightFalloff[c_num_point_lights];
};

#endif