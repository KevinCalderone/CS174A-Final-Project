#ifndef __EFFECTPARAMETERS_H__
#define __EFFECTPARAMETERS_H__

#include <string>

#include "mat.h"

struct EffectParameters
{
	EffectParameters ()
		: m_materialOpacity(1.0f), m_twoSided(0), m_HUDRender(0)
	{}

	// Render Parameters
	bool m_twoSided;
	bool m_HUDRender;

	// Geometry Parameters
	mat4 m_modelviewMatrix;
	float m_animationTime;

	// Texture Channels
	std::string m_diffuseTexture;
	std::string m_normalMap;

	// Material Parameters
	vec3 m_materialAmbient;
	vec3 m_materialDiffuse;
	vec3 m_materialSpecular;
	float m_materialSpecularExponent;
	float m_materialGloss;
	float m_materialOpacity;
};

#endif