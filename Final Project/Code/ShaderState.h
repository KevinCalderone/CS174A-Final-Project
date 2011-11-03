#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include "mat.h"

typedef bool static_branch;

struct ShaderState
{
	mat4 m_projectionMatrix;
	mat4 m_modelviewMatrix;

	static_branch b_useTexture0;
};

#endif