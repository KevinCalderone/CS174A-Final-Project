#ifndef __UBERSHADER_H__
#define __UBERSHADER_H__

#include <string>

#include "ShaderState.h"

class UberShader
{
public:
	UberShader (const std::string& vertShader, const std::string& fragShader);
	virtual ~UberShader ();

	void Apply ();

protected:
	GLuint m_program;
};

#endif