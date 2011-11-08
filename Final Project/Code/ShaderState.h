#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include "mat.h"

#include "GraphicsSettings.h"

typedef int static_branch;

struct ShaderState
{
	mat4 m_projectionMatrix;
	mat4 m_modelviewMatrix;

	static_branch b_useDiffuseTexture;
	static_branch b_useEnvironmentMap;
	static_branch b_useNormalMap;

	vec3 m_eyePosition;

	vec3 m_lightDirection;
	vec3 m_lightCombinedAmbient;
	vec3 m_lightCombinedDiffuse;
	vec3 m_lightCombinedSpecular;
	float m_materialSpecularExponent;
	float m_materialGloss;

	static_branch b_usePointLight[c_num_point_lights];
	vec3 m_pointLightPosition[c_num_point_lights];
	vec3 m_pointLightCombinedAmbient[c_num_point_lights];
	vec3 m_pointLightCombinedDiffuse[c_num_point_lights];
	vec3 m_pointLightCombinedSpecular[c_num_point_lights];
	float m_pointLightRange[c_num_point_lights];
	float m_pointLightAttenuationMultiplier[c_num_point_lights];
};

#endif