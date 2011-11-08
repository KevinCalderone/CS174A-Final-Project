#ifndef __POSTPROCESSSHADER_H__
#define __POSTPROCESSSHADER_H__

#include "UberShader.h"

class PostProcessShader : public UberShader
{
public:
	PostProcessShader (const std::string& vertShader, const std::string& fragShader);
	~PostProcessShader ();

private:
	GLuint m_vPosition;

};

#endif