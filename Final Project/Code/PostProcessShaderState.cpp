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