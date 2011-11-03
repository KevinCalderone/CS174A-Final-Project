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

	GLuint b_useTexture0;

	GLuint m_eyePosition;

	GLuint m_lightDirection;
	GLuint m_lightCombinedAmbient;
	GLuint m_lightCombinedDiffuse;
	GLuint m_lightCombinedSpecular;
	GLuint m_materialSpecularExponent;

	ShaderState m_currentState;
};

#endif