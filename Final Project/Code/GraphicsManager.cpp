#include "GraphicsManager.h"

#include <fstream>

#include "ForwardShader.h"
#include "PostProcessShader.h"
#include "GeometryManager.h"
#include "TextureManager.h"

#include "EffectParameters.h"
#include "RenderParameters.h"

#include "RenderBatch.h"
#include "ShaderState.h"
#include "Geometry.h"

static const float c_num_falloff_range = 0.0001f;	// must be greater than 0

GraphicsManager::GraphicsManager (const std::string& assetLibrary) 
	: m_forwardShader(NULL), m_postProcessShader(NULL), m_geometryManager(NULL), m_textureManager(NULL), m_assetLibrary(assetLibrary)
{
	ReloadAssets();

	glEnable(GL_DEPTH_TEST);
}

GraphicsManager::~GraphicsManager () {
	ClearAssets();
}

void GraphicsManager::ClearAssets () {
	if (m_forwardShader != NULL) {
		delete m_forwardShader;
		m_forwardShader = NULL;
	}
	
	if (m_postProcessShader != NULL) {
		delete m_postProcessShader;
		m_postProcessShader = NULL;
	}

	if (m_geometryManager != NULL) {
		delete m_geometryManager;
		m_geometryManager = NULL;
	}
	
	if (m_textureManager != NULL) {
		delete m_textureManager;
		m_textureManager = NULL;
	}
}

void GraphicsManager::ReloadAssets () {
	ClearAssets();
	
	std::ifstream is;
	is.open (m_assetLibrary.c_str(), std::ios::binary);

	if(!is.is_open()) {
		printf("GraphicsManager::ReloadAssets: Error opening asset library file.");
	}
	else {
		std::string forwardVertShaderFile;
		std::string forwardFragShaderFile;
		std::string postVertShaderFile;
		std::string postFragShaderFile;
		std::string geometryLibrary;
		std::string textureLibrary;
   
		is >> forwardVertShaderFile;
		is >> forwardFragShaderFile;
		is >> postVertShaderFile;
		is >> postFragShaderFile;
		is >> geometryLibrary;
		is >> textureLibrary;

		m_geometryManager = new GeometryManager(geometryLibrary);
		m_forwardShader = new ForwardShader(forwardVertShaderFile, forwardFragShaderFile);
		m_postProcessShader = new PostProcessShader(postVertShaderFile, postFragShaderFile);
		m_textureManager = new TextureManager(textureLibrary);

		InitRenderBuffers();

		is.close();
   }           
}

void GraphicsManager::InitRenderBuffers () {
	// Generate FBO depth buffer
	glGenRenderbuffers(1, &m_fboDepth);   
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, m_fboDepth);  
	glRenderbufferStorage(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, c_window_width, c_window_height); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER_EXT, 0);  

	// Generate FBO color buffer
	glGenTextures(1, &m_fboColor); 
	glBindTexture(GL_TEXTURE_2D, m_fboColor);  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, c_window_width, c_window_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  

	// Generate FBO color buffer
	glGenTextures(1, &m_fboColorHalf); 
	glBindTexture(GL_TEXTURE_2D, m_fboColorHalf);  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, c_window_width / 2, c_window_height / 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  

	// Generate FBO color buffer
	glGenTextures(1, &m_fboColorBlurX); 
	glBindTexture(GL_TEXTURE_2D, m_fboColorBlurX);  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, c_window_width / 2, c_window_height / 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  

	// Generate FBO color buffer
	glGenTextures(1, &m_fboColorBlurXY); 
	glBindTexture(GL_TEXTURE_2D, m_fboColorBlurXY);  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, c_window_width / 2, c_window_height / 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	glBindTexture(GL_TEXTURE_2D, 0);  

	// Generate FBO
	glGenFramebuffers(1, &m_fbo);  
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, m_fbo); 
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboColor, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_fboDepth);
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT); 
  
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {  
		std::cout << "Couldn't create frame buffer" << std::endl; 
		exit(0); 
	}  
}

void GraphicsManager::ClearScreen () {
	// Clear HDR FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo); 
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboColor, 0);
	
	glEnable(GL_DEPTH_TEST);
	glClearColor (0.0f, 0.0f, 1.0f, 1.0f); // Set the clear colour 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the depth and colour buffers 
}

void GraphicsManager::Render (const RenderBatch& batch) {
	if (m_forwardShader == NULL)
		return;

	// Forward render into HDR FBO
	ShaderState state = CalculateShaderState(batch.m_effectParameters);
	m_forwardShader->Apply();
	m_forwardShader->SetShaderState(state);

	if (state.b_useDiffuseTexture)
		m_textureManager->SetTexture(e_TextureChannelDiffuse, batch.m_effectParameters.m_diffuseTexture);

	if (state.b_useEnvironmentMap)
		m_textureManager->SetTexture(e_TextureChannelEnvMap, m_renderParameters.m_environmentMap);

	if (state.b_useNormalMap)
		m_textureManager->SetTexture(e_TextureChannelNormalMap, batch.m_effectParameters.m_normalMap);

	m_geometryManager->RenderGeometry(batch.m_geometryID);
}

void GraphicsManager::SwapBuffers () {
	glDisable(GL_DEPTH_TEST);

	glViewport(0, 0, c_window_width / 2, c_window_height / 2);
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, m_fbo); 
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboColorHalf, 0);

	m_postProcessShader->Apply();
	m_postProcessShader->m_blurX = false;
	m_postProcessShader->m_blurY = false;
	m_postProcessShader->SetShaderState();
	glActiveTexture(e_TextureChannelForwardRender);
	glBindTexture(GL_TEXTURE_2D, m_fboColor);
	m_geometryManager->RenderGeometry("screenQuad");
	
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, m_fbo); 
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboColorBlurX, 0);

	m_postProcessShader->Apply();
	m_postProcessShader->m_blurX = true;
	m_postProcessShader->m_blurY = false;
	m_postProcessShader->SetShaderState();
	glActiveTexture(e_TextureChannelForwardRender);
	glBindTexture(GL_TEXTURE_2D, m_fboColorHalf);
	m_geometryManager->RenderGeometry("screenQuad");
	
	glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_fboColorBlurXY, 0);

	m_postProcessShader->Apply();
	m_postProcessShader->m_blurX = false;
	m_postProcessShader->m_blurY = true;
	m_postProcessShader->SetShaderState();
	glActiveTexture(e_TextureChannelForwardRender);
	glBindTexture(GL_TEXTURE_2D, m_fboColorBlurX);
	m_geometryManager->RenderGeometry("screenQuad");
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
	glClear(GL_DEPTH_BUFFER_BIT);
	
	m_postProcessShader->Apply();
	m_postProcessShader->m_blurX = false;
	m_postProcessShader->m_blurY = false;
	m_postProcessShader->SetShaderState();

	glActiveTexture(e_TextureChannelForwardRender);
	glBindTexture(GL_TEXTURE_2D, m_fboColor);
	
	glActiveTexture(e_TextureChannelForwardRenderBlur);
	glBindTexture(GL_TEXTURE_2D, m_fboColorBlurXY);

	glViewport(0, 0, c_window_width, c_window_height);

	m_geometryManager->RenderGeometry("screenQuad");

	glutSwapBuffers();
}

ShaderState GraphicsManager::CalculateShaderState (const EffectParameters& effectParameters) {
	ShaderState state;

	state.m_projectionMatrix = m_renderParameters.m_projectionMatrix;
	state.m_modelviewMatrix = effectParameters.m_modelviewMatrix;

	state.b_useDiffuseTexture = m_textureManager->HasTexture(effectParameters.m_diffuseTexture);
	state.b_useEnvironmentMap = m_textureManager->HasTexture(m_renderParameters.m_environmentMap);
	state.b_useNormalMap = m_textureManager->HasTexture(effectParameters.m_normalMap);

	state.m_eyePosition = m_renderParameters.m_eyePosition;

	state.m_lightDirection = m_renderParameters.m_lightDirection;
	state.m_lightCombinedAmbient = m_renderParameters.m_lightAmbient * effectParameters.m_materialAmbient;
	state.m_lightCombinedDiffuse = m_renderParameters.m_lightDiffuse * effectParameters.m_materialDiffuse;
	state.m_lightCombinedSpecular = m_renderParameters.m_lightSpecular * effectParameters.m_materialSpecular;
	state.m_materialSpecularExponent = effectParameters.m_materialSpecularExponent;
	state.m_materialGloss = effectParameters.m_materialGloss;

	for (int i = 0; i < c_num_point_lights; ++i) {
		state.m_pointLightCombinedAmbient[i] = m_renderParameters.m_pointLightAmbient[i] * effectParameters.m_materialAmbient;
		state.m_pointLightCombinedDiffuse[i] = m_renderParameters.m_pointLightDiffuse[i] * effectParameters.m_materialDiffuse;
		state.m_pointLightCombinedSpecular[i] = m_renderParameters.m_pointLightSpecular[i] * effectParameters.m_materialSpecular;

		state.b_usePointLight[i] = state.m_pointLightCombinedAmbient[i] != vec3() ||
								   state.m_pointLightCombinedDiffuse[i] != vec3() ||
								   state.m_pointLightCombinedSpecular[i] != vec3();

		if (state.b_usePointLight[i] == false)
			continue;

		state.m_pointLightPosition[i] = m_renderParameters.m_pointLightPosition[i];
		state.m_pointLightRange[i] = m_renderParameters.m_pointLightRange[i];

		float falloffRange = m_renderParameters.m_pointLightRange[i] - m_renderParameters.m_pointLightFalloff[i];
		if (falloffRange < c_num_falloff_range)
			falloffRange = c_num_falloff_range;

		state.m_pointLightAttenuationMultiplier[i] = 1.0f / falloffRange;
	}

	return state;
}