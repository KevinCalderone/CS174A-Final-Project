#ifndef __POSTPROCESSSHADERSTATE_H__
#define __POSTPROCESSSHADERSTATE_H__

#include "ShaderState.h"

struct PostProcessShaderState : public ShaderState
{
	PostProcessShaderState () 
		: b_blurX(false), b_blurY(false), b_depthOfField(false) 
	{}

	void HandleShaderFlags (std::vector<std::string> shaderFlags);

	static_branch b_blurX;
	static_branch b_blurY;
	static_branch b_depthOfField;
};

#endif