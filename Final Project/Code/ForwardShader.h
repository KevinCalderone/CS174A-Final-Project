#ifndef __FORWARDSHADER_H__
#define __FORWARDSHADER_H__

#include <string>

#include "UberShader.h"
#include "ForwardShaderState.h"

class ForwardShader : public UberShader
{
public:
	ForwardShader (const std::string& vertShader, const std::string& fragShader);
	~ForwardShader ();

	void SetShaderState (const ShaderState* shaderState);

private:	
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
	GLuint m_materialOpacity;

	GLuint b_usePointLight;
	GLuint m_pointLightPosition;
	GLuint m_pointLightCombinedAmbient;
	GLuint m_pointLightCombinedDiffuse;
	GLuint m_pointLightCombinedSpecular;
	GLuint m_pointLightRange;
	GLuint m_pointLightAttenuationMultiplier;

	ForwardShaderState m_currentState;
};

#endif