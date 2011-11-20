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

	m_colorCorrection = glGetUniformLocation(m_program, "colorCorrection");
	m_randSeed = glGetUniformLocation(m_program, "randSeed");

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "renderPassSource0"), e_TextureChannelRenderPassSource0 - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "renderPassSource1"), e_TextureChannelRenderPassSource1 - e_TextureChannelFirst);
}

PostProcessShader::~PostProcessShader () {

}

void PostProcessShader::SetShaderState (const ShaderState* shaderState) {
	const PostProcessShaderState* postProcessShaderState = (PostProcessShaderState*)shaderState;

	glUniform1i(b_blurX, postProcessShaderState->b_blurX);
	glUniform1i(b_blurY, postProcessShaderState->b_blurY);
	glUniform1i(b_depthOfField, postProcessShaderState->b_depthOfField);

	glUniformMatrix4fv(m_colorCorrection, 1, GL_TRUE, (GLfloat*)&postProcessShaderState->m_colorCorrection);
	glUniform1i(m_randSeed, postProcessShaderState->m_randSeed);

 	glEnableVertexAttribArray(m_vPosition);
	glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(postProcessShaderState->m_attributeLocation.m_position0));

	m_currentState = *postProcessShaderState;
}
