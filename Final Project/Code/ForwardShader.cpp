#include "ForwardShader.h"

#include "Angel.h"

#include "GraphicsSettings.h"
#include "Vertex.h"

ForwardShader::ForwardShader (const std::string& vertShader, const std::string& fragShader)
	: UberShader(vertShader, fragShader)
{
	// Initialize location of shader variables
	m_vPosition = glGetAttribLocation(m_program, "vPosition");
	m_vNormal = glGetAttribLocation(m_program, "vNormal");
	m_vTexCoord = glGetAttribLocation(m_program, "vTexCoord");

	m_projectionMatrix = glGetUniformLocation(m_program, "projectionMatrix");
	m_modelviewMatrix = glGetUniformLocation(m_program, "modelviewMatrix");

	b_useDiffuseTexture = glGetUniformLocation(m_program, "b_useDiffuseTexture");
	b_useEnvironmentMap = glGetUniformLocation(m_program, "b_useEnvironmentMap");
	b_useNormalMap = glGetUniformLocation(m_program, "b_useNormalMap");

	m_eyePosition = glGetUniformLocation(m_program, "eyePosition");

	m_lightDirection = glGetUniformLocation(m_program, "lightDirection");
	m_lightCombinedAmbient = glGetUniformLocation(m_program, "lightCombinedAmbient");
	m_lightCombinedDiffuse = glGetUniformLocation(m_program, "lightCombinedDiffuse");
	m_lightCombinedSpecular = glGetUniformLocation(m_program, "lightCombinedSpecular");
	m_materialSpecularExponent = glGetUniformLocation(m_program, "materialSpecularExponent");
	m_materialGloss = glGetUniformLocation(m_program, "materialGloss");

	b_usePointLight = glGetUniformLocation(m_program, "b_usePointLight");
	m_pointLightPosition = glGetUniformLocation(m_program, "pointLightPosition");
	m_pointLightCombinedAmbient = glGetUniformLocation(m_program, "pointLightCombinedAmbient");
	m_pointLightCombinedDiffuse = glGetUniformLocation(m_program, "pointLightCombinedDiffuse");
	m_pointLightCombinedSpecular = glGetUniformLocation(m_program, "pointLightCombinedSpecular");
	m_pointLightRange = glGetUniformLocation(m_program, "pointLightRange");
	m_pointLightAttenuationMultiplier = glGetUniformLocation(m_program, "pointLightAttenuationMultiplier");

    glEnableVertexAttribArray(m_vPosition);
    glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

    glEnableVertexAttribArray(m_vNormal);
    glVertexAttribPointer(m_vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_normalDataOffset));

	glEnableVertexAttribArray(m_vTexCoord);
    glVertexAttribPointer(m_vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_texCoord0DataOffset));

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "diffuseTexture"), e_TextureChannelDiffuse - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "environmentMap"), e_TextureChannelEnvMap - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "normalMap"), e_TextureChannelNormalMap - e_TextureChannelFirst);

	ForwardShaderState state;
	SetShaderState(state);
}

ForwardShader::~ForwardShader () {

}

void ForwardShader::SetShaderState (const ForwardShaderState& shaderState) {\
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_TRUE, (GLfloat*)&shaderState.m_projectionMatrix);
	glUniformMatrix4fv(m_modelviewMatrix, 1, GL_TRUE, (GLfloat*)&shaderState.m_modelviewMatrix);

	glUniform1i(b_useDiffuseTexture, shaderState.b_useDiffuseTexture);
	glUniform1i(b_useEnvironmentMap, shaderState.b_useEnvironmentMap);
	glUniform1i(b_useNormalMap, shaderState.b_useNormalMap);

	glUniform3fv(m_eyePosition, 1, shaderState.m_eyePosition);

	glUniform3fv(m_lightDirection, 1, shaderState.m_lightDirection);
	glUniform3fv(m_lightCombinedAmbient, 1, shaderState.m_lightCombinedAmbient);
	glUniform3fv(m_lightCombinedDiffuse, 1, shaderState.m_lightCombinedDiffuse);
	glUniform3fv(m_lightCombinedSpecular, 1, shaderState.m_lightCombinedSpecular);
	glUniform1f(m_materialSpecularExponent, shaderState.m_materialSpecularExponent);
	glUniform1f(m_materialGloss, shaderState.m_materialGloss);

	glUniform1iv(b_usePointLight, c_num_point_lights, shaderState.b_usePointLight);
	glUniform3fv(m_pointLightPosition, c_num_point_lights, (GLfloat*)shaderState.m_pointLightPosition);
	glUniform3fv(m_pointLightCombinedAmbient, c_num_point_lights, (GLfloat*)shaderState.m_pointLightCombinedAmbient);
	glUniform3fv(m_pointLightCombinedDiffuse, c_num_point_lights, (GLfloat*)shaderState.m_pointLightCombinedDiffuse);
	glUniform3fv(m_pointLightCombinedSpecular, c_num_point_lights, (GLfloat*)shaderState.m_pointLightCombinedSpecular);
	glUniform1fv(m_pointLightRange, c_num_point_lights, shaderState.m_pointLightRange);
	glUniform1fv(m_pointLightAttenuationMultiplier, c_num_point_lights, shaderState.m_pointLightAttenuationMultiplier);

	m_currentState = shaderState;
}