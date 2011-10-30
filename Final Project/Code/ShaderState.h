#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include "mat.h"

typedef bool static_branch;

struct ShaderState
{
	mat4 m_modelView;
	mat4 m_projection;

	static_branch b_useTexture0;
	GLuint m_texture0;
};

#endif