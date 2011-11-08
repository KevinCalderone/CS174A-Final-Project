#include "PostProcessShader.h"

#include "Angel.h"

#include "Vertex.h"

PostProcessShader::PostProcessShader (const std::string& vertShader, const std::string& fragShader)
	: UberShader(vertShader, fragShader)
{
	m_vPosition = glGetAttribLocation(m_program, "vPosition");

	glEnableVertexAttribArray(m_vPosition);
	glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(c_positionDataOffset));

	// bind samplers to texture units
	glUniform1i(glGetUniformLocation(m_program, "forwardRenderedResult"), e_TextureChannelForwardRender - e_TextureChannelFirst);
}

PostProcessShader::~PostProcessShader () {

}
