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

	b_useTexture0 = glGetUniformLocation(m_program, "b_useTexture0");
	m_texture0 = glGetUniformLocation(m_program, "texture0");

    glEnableVertexAttribArray(m_vPosition);
    glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

    glEnableVertexAttribArray(m_vNormal);
    glVertexAttribPointer(m_vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_normalDataOffset));

	glEnableVertexAttribArray(m_vTexCoord);
    glVertexAttribPointer(m_vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_texCoord0DataOffset));
		
	glUniform1i(m_texture0, 0);
	
	ShaderState state;
	SetShaderState(state);
}

UberShader::~UberShader () {

}

void UberShader::SetShaderState (const ShaderState& shaderState) {
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_TRUE, (GLfloat*)&shaderState.m_projectionMatrix);
	glUniformMatrix4fv(m_modelviewMatrix, 1, GL_TRUE, (GLfloat*)&shaderState.m_modelviewMatrix);

	glUniform1i(b_useTexture0, shaderState.b_useTexture0);

	m_currentState = shaderState;
}
