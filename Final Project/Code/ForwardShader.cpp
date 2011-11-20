#include "ForwardShader.h"

#include "Angel.h"

#include "GraphicsSettings.h"
#include "Vertex.h"

ForwardShader::ForwardShader (const std::string& vertShader, const std::string& fragShader)
	: UberShader(vertShader, fragShader)
{
	b_animatedGeometry = glGetUniformLocation(m_program, "b_animatedGeometry");
	m_attributeLerp = glGetUniformLocation(m_program, "attributeLerp");

	m_vPosition0 = glGetAttribLocation(m_program, "vPosition0");
	m_vNormal0 = glGetAttribLocation(m_program, "vNormal0");
	m_vTexCoord0 = glGetAttribLocation(m_program, "vTexCoord0");

	m_vPosition1 = glGetAttribLocation(m_program, "vPosition1");
	m_vNormal1 = glGetAttribLocation(m_program, "vNormal1");
	m_vTexCoord1 = glGetAttribLocation(m_program, "vTexCoord1");

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
	m_materialOpacity = glGetUniformLocation(m_program, "materialOpacity");

	b_usePointLight = glGetUniformLocation(m_program, "b_usePointLight");
	m_pointLightPosition = glGetUniformLocation(m_program, "pointLightPosition");
	m_pointLightCombinedAmbient = glGetUniformLocation(m_program, "pointLightCombinedAmbient");
	m_pointLightCombinedDiffuse = glGetUniformLocation(m_program, "pointLightCombinedDiffuse");
	m_pointLightCombinedSpecular = glGetUniformLocation(m_program, "pointLightCombinedSpecular");
	m_pointLightRange = glGetUniformLocation(m_program, "pointLightRange");
	m_pointLightAttenuationMultiplier = glGetUniformLocation(m_program, "pointLightAttenuationMultiplier");

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "diffuseTexture"), e_TextureChannelDiffuse - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "environmentMap"), e_TextureChannelEnvMap - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "normalMap"), e_TextureChannelNormalMap - e_TextureChannelFirst);

	ForwardShaderState state;
	SetShaderState(&state);
}

ForwardShader::~ForwardShader () {

}

void ForwardShader::SetShaderState (const ShaderState* shaderState) {
	const ForwardShaderState* forwardShaderState = (ForwardShaderState*)shaderState;

	glUniform1i(b_animatedGeometry, forwardShaderState->m_attributeLocation.m_animatedGeometry ? 1 : 0);

	glUniformMatrix4fv(m_projectionMatrix, 1, GL_TRUE, (GLfloat*)&forwardShaderState->m_projectionMatrix);
	glUniformMatrix4fv(m_modelviewMatrix, 1, GL_TRUE, (GLfloat*)&forwardShaderState->m_modelviewMatrix);

	glUniform1i(b_useDiffuseTexture, forwardShaderState->b_useDiffuseTexture);
	glUniform1i(b_useEnvironmentMap, forwardShaderState->b_useEnvironmentMap);
	glUniform1i(b_useNormalMap, forwardShaderState->b_useNormalMap);

	glUniform3fv(m_eyePosition, 1, forwardShaderState->m_eyePosition);

	glUniform3fv(m_lightDirection, 1, forwardShaderState->m_lightDirection);
	glUniform3fv(m_lightCombinedAmbient, 1, forwardShaderState->m_lightCombinedAmbient);
	glUniform3fv(m_lightCombinedDiffuse, 1, forwardShaderState->m_lightCombinedDiffuse);
	glUniform3fv(m_lightCombinedSpecular, 1, forwardShaderState->m_lightCombinedSpecular);
	glUniform1f(m_materialSpecularExponent, forwardShaderState->m_materialSpecularExponent);
	glUniform1f(m_materialGloss, forwardShaderState->m_materialGloss);
	glUniform1f(m_materialOpacity, forwardShaderState->m_materialOpacity);

	glUniform1iv(b_usePointLight, c_num_point_lights, forwardShaderState->b_usePointLight);
	glUniform3fv(m_pointLightPosition, c_num_point_lights, (GLfloat*)forwardShaderState->m_pointLightPosition);
	glUniform3fv(m_pointLightCombinedAmbient, c_num_point_lights, (GLfloat*)forwardShaderState->m_pointLightCombinedAmbient);
	glUniform3fv(m_pointLightCombinedDiffuse, c_num_point_lights, (GLfloat*)forwardShaderState->m_pointLightCombinedDiffuse);
	glUniform3fv(m_pointLightCombinedSpecular, c_num_point_lights, (GLfloat*)forwardShaderState->m_pointLightCombinedSpecular);
	glUniform1fv(m_pointLightRange, c_num_point_lights, forwardShaderState->m_pointLightRange);
	glUniform1fv(m_pointLightAttenuationMultiplier, c_num_point_lights, forwardShaderState->m_pointLightAttenuationMultiplier);

    glEnableVertexAttribArray(m_vPosition0);
	glVertexAttribPointer(m_vPosition0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_position0));
		
	glEnableVertexAttribArray(m_vNormal0);
	glVertexAttribPointer(m_vNormal0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_normal0));
		
	glEnableVertexAttribArray(m_vTexCoord0);
	glVertexAttribPointer(m_vTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_texCoord0));

	if (forwardShaderState->m_attributeLocation.m_animatedGeometry) {
		glEnableVertexAttribArray(m_vPosition1);
		glVertexAttribPointer(m_vPosition1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_position1));

		glEnableVertexAttribArray(m_vNormal1);
		glVertexAttribPointer(m_vNormal1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_normal1));
				
		glEnableVertexAttribArray(m_vTexCoord1);
		glVertexAttribPointer(m_vTexCoord1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(forwardShaderState->m_attributeLocation.m_texCoord1));

		glUniform1f(m_attributeLerp, forwardShaderState->m_attributeLerp);
	}
	else {
		glDisableVertexAttribArray(m_vPosition1);
		glDisableVertexAttribArray(m_vNormal1);
	}

	m_currentState = *forwardShaderState;
}