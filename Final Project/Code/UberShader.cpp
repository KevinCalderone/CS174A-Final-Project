#include "UberShader.h"

#include "Angel.h"
#include "Vertex.h"

UberShader::UberShader (const std::string& vertShader, const std::string& fragShader) {

	m_program = InitShader(vertShader.c_str(), fragShader.c_str());
    glUseProgram( m_program );

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

    glEnableVertexAttribArray(m_vPosition);
    glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

    glEnableVertexAttribArray(m_vNormal);
    glVertexAttribPointer(m_vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_normalDataOffset));

	glEnableVertexAttribArray(m_vTexCoord);
    glVertexAttribPointer(m_vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_texCoord0DataOffset));
	
	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(m_program, "environmentMap"), 1);
	glUniform1i(glGetUniformLocation(m_program, "normalMap"), 2);

	ShaderState state;
	SetShaderState(state);
}

UberShader::~UberShader () {

}

void UberShader::SetShaderState (const ShaderState& shaderState) {
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

	m_currentState = shaderState;
}
