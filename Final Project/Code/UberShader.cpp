#include "UberShader.h"

UberShader::UberShader (const std::string& vertShader, const std::string& fragShader) {
	m_program = InitShader(vertShader.c_str(), fragShader.c_str());
    glUseProgram(m_program);
}

UberShader::~UberShader () {
	GLsizei count;
	GLuint shaders[2];
	glGetAttachedShaders(m_program, 2, &count, &shaders[0]);

	for (int i = 0; i < count; ++i)
		glDeleteShader(shaders[i]);

	glDeleteProgram(m_program);		
}

void UberShader::Apply () {
	glUseProgram(m_program);
}