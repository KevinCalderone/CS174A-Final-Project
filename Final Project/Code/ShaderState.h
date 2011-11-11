#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__

#include <string>
#include <vector>

typedef int static_branch;

struct ShaderState
{
	virtual void HandleShaderFlags (std::vector<std::string> shaderFlags) = 0;
};

#endif