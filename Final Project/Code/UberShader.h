#ifndef __UBERMANAGER_H__
#define __UBERMANAGER_H__

#include <string>

#include "ShaderState.h"

class UberShader
{
public:
	UberShader (const std::string& vertShader, const std::string& fragShader);
	~UberShader ();

	void SetShaderState (const ShaderState& shaderState);
private:
	GLuint m_program;
	
	GLuint m_vPosition;
	GLuint m_vNormal;
	GLuint m_vTexCoord;

	GLuint m_projectionMatrix;
	GLuint m_modelviewMatrix;

	GLuint b_useDiffuseTexture;
	GLuint b_useEnvironmentMap;
	GLuint b_useNormalMap;

	GLuint m_eyePosition;

	GLuint m_lightDirection;
	GLuint m_lightCombinedAmbient;
	GLuint m_lightCombinedDiffuse;
	GLuint m_lightCombinedSpecular;
	GLuint m_materialSpecularExponent;
	GLuint m_materialGloss;

	GLuint b_usePointLight;
	GLuint m_pointLightPosition;
	GLuint m_pointLightCombinedAmbient;
	GLuint m_pointLightCombinedDiffuse;
	GLuint m_pointLightCombinedSpecular;
	GLuint m_pointLightRange;
	GLuint m_pointLightAttenuationMultiplier;

	ShaderState m_currentState;
};

#endif