#include "ForwardShaderState.h"

void ForwardShaderState::HandleShaderFlags (std::vector<std::string> shaderFlags) {
	for (std::vector<std::string>::iterator flagIter = shaderFlags.begin(); flagIter != shaderFlags.end(); ++flagIter) {
		printf("ForwardShaderState::HandleShaderFlags: Warning: Unhandle RenderPass flag %s\n", (*flagIter).c_str());
	}
}