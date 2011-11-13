#ifndef __UBERSHADER_H__
#define __UBERSHADER_H__

#include <string>

#include "Angel.h"

#include "ShaderState.h"

class UberShader
{
public:
	UberShader (const std::string& vertShader, const std::string& fragShader);
	virtual ~UberShader ();

	void Apply ();
	virtual void SetShaderState (const ShaderState* shaderState) = 0;

protected:
	GLuint m_program;
};

#endif