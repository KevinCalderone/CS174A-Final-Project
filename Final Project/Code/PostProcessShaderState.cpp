#include "PostProcessShaderState.h"

void PostProcessShaderState::HandleShaderFlags (std::vector<std::string> shaderFlags) {
	for (std::vector<std::string>::iterator flagIter = shaderFlags.begin(); flagIter != shaderFlags.end(); ++flagIter) {
		if (*flagIter == "blurX") {
			b_blurX = true;
		}
		else if (*flagIter == "blurY") {
			b_blurY = true;
		}
		else if (*flagIter == "depthOfField") {
			b_depthOfField = true;
		}
		else {
			printf("PostProcessShaderState::HandleShaderFlags: Warning: Unhandle RenderPass flag %s\n", (*flagIter).c_str());
		}
	}
}

void PostProcessShaderState::CalculateShaderState (const RenderParameters& renderParameters, const EffectParameters& effectParameters) {
	m_colorCorrection = renderParameters.m_colorCorrection;
	m_randSeed = rand();
}
