#include "ForwardShaderState.h"

#include "GraphicsSettings.h"

void ForwardShaderState::HandleShaderFlags (std::vector<std::string> shaderFlags) {
	for (std::vector<std::string>::iterator flagIter = shaderFlags.begin(); flagIter != shaderFlags.end(); ++flagIter) {
		printf("ForwardShaderState::HandleShaderFlags: Warning: Unhandle RenderPass flag %s\n", (*flagIter).c_str());
	}
}

void ForwardShaderState::CalculateShaderState (const RenderParameters& renderParameters, const EffectParameters& effectParameters) {
	m_projectionMatrix = renderParameters.m_projectionMatrix;
	m_modelviewMatrix = effectParameters.m_modelviewMatrix;

	m_eyePosition = renderParameters.m_eyePosition;

	m_lightDirection = renderParameters.m_lightDirection;
	m_lightCombinedAmbient = renderParameters.m_lightAmbient * effectParameters.m_materialAmbient;
	m_lightCombinedDiffuse = renderParameters.m_lightDiffuse * effectParameters.m_materialDiffuse;
	m_lightCombinedSpecular = renderParameters.m_lightSpecular * effectParameters.m_materialSpecular;
	m_materialSpecularExponent = effectParameters.m_materialSpecularExponent;
	m_materialGloss = effectParameters.m_materialGloss;
	m_materialOpacity = effectParameters.m_materialOpacity;

	for (int i = 0; i < c_num_point_lights; ++i) {
		m_pointLightCombinedAmbient[i] = renderParameters.m_pointLightAmbient[i] * effectParameters.m_materialAmbient;
		m_pointLightCombinedDiffuse[i] = renderParameters.m_pointLightDiffuse[i] * effectParameters.m_materialDiffuse;
		m_pointLightCombinedSpecular[i] = renderParameters.m_pointLightSpecular[i] * effectParameters.m_materialSpecular;

		b_usePointLight[i] = m_pointLightCombinedAmbient[i] != vec3() ||
							 m_pointLightCombinedDiffuse[i] != vec3() ||
								   m_pointLightCombinedSpecular[i] != vec3();

		if (b_usePointLight[i] == false)
			continue;

		m_pointLightPosition[i] = renderParameters.m_pointLightPosition[i];
		m_pointLightRange[i] = renderParameters.m_pointLightRange[i];

		float falloffRange = renderParameters.m_pointLightRange[i] - renderParameters.m_pointLightFalloff[i];
		if (falloffRange < c_num_falloff_range)
			falloffRange = c_num_falloff_range;

		m_pointLightAttenuationMultiplier[i] = 1.0f / falloffRange;
	}
}