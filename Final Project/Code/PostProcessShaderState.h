#ifndef __POSTPROCESSSHADERSTATE_H__
#define __POSTPROCESSSHADERSTATE_H__

#include "Angel.h"

#include "ShaderState.h"
#include "mat.h"

struct PostProcessShaderState : public ShaderState
{
	PostProcessShaderState () 
		: b_blurX(false), b_blurY(false), b_depthOfField(false) 
	{}

	void HandleShaderFlags (std::vector<std::string> shaderFlags);
	void CalculateShaderState (const RenderParameters& renderParameters, const EffectParameters& effectParameters);

	static_branch b_blurX;
	static_branch b_blurY;
	static_branch b_depthOfField;

	mat4 m_colorCorrection;
	int m_randSeed;
};

#endif