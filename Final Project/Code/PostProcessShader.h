#ifndef __POSTPROCESSSHADER_H__
#define __POSTPROCESSSHADER_H__

#include "UberShader.h"

#include "PostProcessShaderState.h"

class PostProcessShader : public UberShader
{
public:
	PostProcessShader (const std::string& vertShader, const std::string& fragShader);
	~PostProcessShader ();

	void SetShaderState (const ShaderState* shaderState);
	void HandleShaderFlags (std::vector<std::string> shaderFlags);

private:
	GLuint m_vPosition;

	GLuint b_blurX;
	GLuint b_blurY;
	GLuint b_depthOfField;

	GLuint m_colorCorrection;
	GLuint m_randSeed;

	GLuint m_windowWidth;
	GLuint m_windowHeight;

	PostProcessShaderState m_currentState;
};

#endif