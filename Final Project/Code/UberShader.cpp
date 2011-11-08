#include "UberShader.h"

UberShader::UberShader (const std::string& vertShader, const std::string& fragShader) {
	m_program = InitShader(vertShader.c_str(), fragShader.c_str());
    glUseProgram(m_program);
}

UberShader::~UberShader () {
	glDeleteProgram(m_program);
}

void UberShader::Apply () {
	glUseProgram(m_program);
}