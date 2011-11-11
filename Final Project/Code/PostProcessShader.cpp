#include "PostProcessShader.h"

#include "Angel.h"

#include "GraphicsSettings.h"
#include "Vertex.h"

PostProcessShader::PostProcessShader (const std::string& vertShader, const std::string& fragShader)
	: UberShader(vertShader, fragShader)
{
	m_vPosition = glGetAttribLocation(m_program, "vPosition");

	b_blurX = glGetUniformLocation(m_program, "b_blurX");
	b_blurY = glGetUniformLocation(m_program, "b_blurY");
	b_depthOfField = glGetUniformLocation(m_program, "b_depthOfField");

	glEnableVertexAttribArray(m_vPosition);
	glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "renderPassSource0"), e_TextureChannelRenderPassSource0 - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "renderPassSource1"), e_TextureChannelRenderPassSource1 - e_TextureChannelFirst);
}

PostProcessShader::~PostProcessShader () {

}

void PostProcessShader::SetShaderState (const PostProcessShaderState& shaderState) {

	glUniform1i(b_blurX, shaderState.b_blurX);
	glUniform1i(b_blurY, shaderState.b_blurY);
	glUniform1i(b_depthOfField, shaderState.b_depthOfField);

	m_currentState = shaderState;
}
