#include "PostProcessShader.h"

#include "Angel.h"

#include "Vertex.h"

PostProcessShader::PostProcessShader (const std::string& vertShader, const std::string& fragShader)
	: UberShader(vertShader, fragShader)
{
	m_vPosition = glGetAttribLocation(m_program, "vPosition");

	b_blurX = glGetUniformLocation(m_program, "b_blurX");
	b_blurY = glGetUniformLocation(m_program, "b_blurY");

	glEnableVertexAttribArray(m_vPosition);
	glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "forwardRenderedResult"), e_TextureChannelForwardRender - e_TextureChannelFirst);
	glUniform1i(glGetUniformLocation(m_program, "forwardRenderedResultBlur"), e_TextureChannelForwardRenderBlur - e_TextureChannelFirst);
}

PostProcessShader::~PostProcessShader () {

}

void PostProcessShader::SetShaderState () {
		
	glUniform1i(b_blurX, m_blurX);
	glUniform1i(b_blurY, m_blurY);

}