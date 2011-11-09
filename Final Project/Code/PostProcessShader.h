#ifndef __POSTPROCESSSHADER_H__
#define __POSTPROCESSSHADER_H__

#include "UberShader.h"

class PostProcessShader : public UberShader
{
public:
	PostProcessShader (const std::string& vertShader, const std::string& fragShader);
	~PostProcessShader ();

	void SetShaderState ();

	bool m_blurX;
	bool m_blurY;

private:
	GLuint m_vPosition;

	GLuint b_blurX;
	GLuint b_blurY;
};

#endif