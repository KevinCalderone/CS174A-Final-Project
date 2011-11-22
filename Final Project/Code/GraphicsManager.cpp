#include "GraphicsManager.h"

#include <fstream>

#include "ForwardShader.h"
#include "PostProcessShader.h"
#include "GeometryManager.h"
#include "TextureManager.h"

#include "EffectParameters.h"
#include "RenderParameters.h"

#include "FrameBufferTexture.h"
#include "RenderPass.h"

#include "RenderBatch.h"
#include "CachedRenderBatch.h"
#include "ForwardShaderState.h"
#include "Geometry.h"

GraphicsManager::GraphicsManager (const std::string& assetLibrary) 
	: m_forwardShader(NULL), m_postProcessShader(NULL), m_geometryManager(NULL), m_textureManager(NULL), m_assetLibrary(assetLibrary)
{
	ReloadAssets();

	glAlphaFunc(GL_GREATER,0.1f);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	m_renderPasses.clear();

	for (std::map<std::string, FrameBufferTexture*>::iterator iter = m_frameBufferTextures.begin(); iter != m_frameBufferTextures.end(); ++iter)
		delete iter->second;

	m_frameBufferTextures.clear();

	glDeleteFramebuffers(1, &m_fbo);
}

void GraphicsManager::ReloadAssets () {
	ClearAssets();
	
	std::ifstream is;
	is.open (m_assetLibrary.c_str(), std::ios::binary);

	if(!is.is_open()) {
		printf("GraphicsManager::ReloadAssets: Error opening asset library file.");
	}
	else {
		std::string effectFile;
		std::string geometryLibrary;
		std::string textureLibrary;
   
		is >> effectFile;
		is >> geometryLibrary;
		is >> textureLibrary;

		is.close();

		glGenFramebuffers(1, &m_fbo);  

		m_geometryManager = new GeometryManager(geometryLibrary);
		LoadEffectFile (effectFile);	// Dependent upon vertex buffers being setup
		m_textureManager = new TextureManager(textureLibrary);
   }           
}

void GraphicsManager::LoadEffectFile (const std::string& effectFile) {
	std::ifstream is;
	is.open (effectFile.c_str(), std::ios::binary);

	if(!is.is_open()) {
		printf("GraphicsManager::LoadEffectFile: Error opening effect file.");
		return;
	}

	while (is.good()) {
		std::string header;
		is >> header;      

		if (header == "shaders") {
			int numSections = 0;
			is >> numSections;

			while (numSections--) {
				std::string shaderName;
				std::string vertexShader;
				std::string fragmentShader;

				is >> shaderName >> vertexShader >> fragmentShader;

				// Only supports staticly defined shaders
				if (shaderName == "forward") {
					if (m_forwardShader != NULL)
						delete m_forwardShader;
					m_forwardShader = new ForwardShader(vertexShader, fragmentShader);
				}
				else if (shaderName == "postProcess") {
					if (m_postProcessShader != NULL)
						delete m_postProcessShader;
					m_postProcessShader = new PostProcessShader(vertexShader, fragmentShader);
				}
			}
		}
		else if (header == "buffers") {
			int numSections = 0;
			is >> numSections;

			while (numSections--) {
				std::string bufferName;
				std::string bufferFormat;
				float widthRatio;
				float heightRatio;

				is >> bufferName >> bufferFormat >> widthRatio >> heightRatio;
				
				std::map<std::string, FrameBufferTexture*>::iterator iter = m_frameBufferTextures.find(bufferName);
				if (iter != m_frameBufferTextures.end())
					continue;

				FrameBufferTexture* texture = new FrameBufferTexture(bufferFormat, c_window_width * widthRatio, c_window_height * heightRatio);
				m_frameBufferTextures[bufferName] = texture;
			}
		}
		else if (header == "passes") {
			int numSections = 0;
			is >> numSections;

			while (numSections--) {
				std::string passName;
				int numOptions = 0;

				is >> passName >> numOptions;

				RenderPass renderPass;

				while (numOptions--) {
					std::string settingType;

					is >> settingType;

					if (settingType == "shader") {
						std::string shaderType;

						is >> shaderType;

						if (shaderType == "forward") {
							renderPass.m_shaderType = e_ShaderTypeForward;
						}
						else if (shaderType == "postProcess") {
							renderPass.m_shaderType = e_ShaderTypePostProcess;
						}
					}
					else if (settingType == "geometry") {
						std::string geometryType;

						is >> geometryType;

						if (geometryType == "opaqueRenderBatches") {
							renderPass.m_geometryType = e_GeometryTypeOpaque;
						}
						else if (geometryType == "transparentRenderBatches") {
							renderPass.m_geometryType = e_GeometryTypeTransparent;
						}
						else if (geometryType == "HUDRenderBatches") {
							renderPass.m_geometryType = e_GeometryTypeHUD;
						}
						else if (geometryType == "screenQuad") {
							renderPass.m_geometryType = e_GeometryTypeScreenQuad;
						}
					}
					else if (settingType == "colorAttach0") {
						is >> renderPass.m_colorAttach0;
					}
					else if (settingType == "depthAttach") {
						is >> renderPass.m_depthAttach;
					}
					else if (settingType == "source0") {
						is >> renderPass.m_source0;
					}
					else if (settingType == "source1") {
						is >> renderPass.m_source1;
					}
					else if (settingType == "flags") {
						int numFlags = 0;

						is >> numFlags;

						while (numFlags--) {
							std::string flagName;

							is >> flagName;

							renderPass.m_flags.push_back(flagName);
						}
					}
				}

				m_renderPasses.push_back(renderPass);
			}
		}
	}
}

void GraphicsManager::ClearScreen () {
	m_cachedRenderBatches[e_GeometryTypeOpaque].clear();
	m_cachedRenderBatches[e_GeometryTypeTransparent].clear();
	m_cachedRenderBatches[e_GeometryTypeHUD].clear();
	m_cachedRenderBatches[e_GeometryTypeScreenQuad].clear();
}

void GraphicsManager::Render (const RenderBatch& batch) {
	if (batch.m_effectParameters.m_HUDRender)
		m_cachedRenderBatches[e_GeometryTypeHUD].push_back(CachedRenderBatch(batch, m_renderParameters));
	else if (batch.m_effectParameters.m_materialOpacity < 1.0f || m_textureManager->IsTransparent(batch.m_effectParameters.m_diffuseTexture))
		m_cachedRenderBatches[e_GeometryTypeTransparent].push_back(CachedRenderBatch(batch, m_renderParameters));
	else
		m_cachedRenderBatches[e_GeometryTypeOpaque].push_back(CachedRenderBatch(batch, m_renderParameters));
}

void GraphicsManager::SwapBuffers () {
	if (m_forwardShader == NULL || m_postProcessShader == NULL)
		return;
	
	// Add the screenQuad batch for the postProcess step
	RenderBatch screenQuad;
	screenQuad.m_geometryID = "screenQuad";
	m_cachedRenderBatches[e_GeometryTypeScreenQuad].push_back(CachedRenderBatch(screenQuad, m_renderParameters));

	for (std::vector<RenderPass>::iterator passIter = m_renderPasses.begin(); passIter != m_renderPasses.end(); ++passIter) {
		unsigned int destinationWidth;
		unsigned int destinationHeight;

		// Setup FBO targets
		if (passIter->m_colorAttach0 == "screen") {	
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

			destinationWidth = c_window_width;
			destinationHeight = c_window_height;

			glDisable(GL_DEPTH_TEST);
		}
		else {
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
			
			const FrameBufferTexture* colorAttach0 = GetFrameBufferTexture(passIter->m_colorAttach0);
			const FrameBufferTexture* depthAttach = GetFrameBufferTexture(passIter->m_depthAttach);

			if (colorAttach0 == NULL) {
				printf("GraphicsManager::SwapBuffers: Invalid destination buffer %s\n", passIter->m_colorAttach0.c_str());
				return;
			}
			else {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttach0->GetBufferTextureID(), 0);

				destinationWidth = colorAttach0->GetBufferTextureWidth();
				destinationHeight = colorAttach0->GetBufferTextureHeight();
			}

			if (depthAttach == NULL) {
				glDisable(GL_DEPTH_TEST);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
			}
			else {
				glEnable(GL_DEPTH_TEST);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthAttach->GetBufferTextureID(), 0);	
			}
		}

		// Setup Render Viewport to the full destination size
		glViewport(0, 0, destinationWidth, destinationHeight);

		// Process RenderPass flags
		unsigned int clearFlags = 0;
		bool blend = false;
		bool alphaTest = false;

		std::vector<std::string> shaderStateFlags;
		for (std::vector<std::string>::iterator flagIter = passIter->m_flags.begin(); flagIter != passIter->m_flags.end(); ++flagIter) {
			if (*flagIter == "clearColor") {
				clearFlags |= GL_COLOR_BUFFER_BIT;
			}
			else if (*flagIter == "clearDepth") {
				clearFlags |= GL_DEPTH_BUFFER_BIT;
			}
			else if (*flagIter == "blend") {
				blend = true;
			}
			else if (*flagIter == "alphaTest") {
				alphaTest = true;
			}
			// Let shader state try to handle the flag
			else {
				shaderStateFlags.push_back(*flagIter);
			}
		}

		// Setup blending mode
		if (blend)  {
			glEnable(GL_BLEND);
			glDepthMask(false);
		}
		else { 
			glDisable(GL_BLEND);
			glDepthMask(true);
		}

		if (alphaTest)
			glEnable(GL_ALPHA_TEST);
		else
			glDisable(GL_ALPHA_TEST);
		
		// Clear buffers specified in flags
		if (clearFlags != 0) 
			glClear(clearFlags);

		UberShader* shader;
		ShaderState* state;

		// Select the shader
		switch (passIter->m_shaderType) {
			case e_ShaderTypeForward:
				shader = m_forwardShader;
				state = new ForwardShaderState();
			break;
	
			case e_ShaderTypePostProcess:
				shader = m_postProcessShader;
				state = new PostProcessShaderState();
			break;		
		};

		if (shader == NULL)
			continue;

		shader->Apply();
		state->HandleShaderFlags(shaderStateFlags);

		// Setup source textures
		const FrameBufferTexture* source0 = GetFrameBufferTexture(passIter->m_source0);
		const FrameBufferTexture* source1 = GetFrameBufferTexture(passIter->m_source1);
		
		state->b_source0 = source0 != NULL;
		state->b_source1 = source1 != NULL;

		if (state->b_source0) {
			glActiveTexture(e_TextureChannelRenderPassSource0);
			glBindTexture(GL_TEXTURE_2D, source0->GetBufferTextureID());
		}	

		if (state->b_source1) {
			glActiveTexture(e_TextureChannelRenderPassSource1);
			glBindTexture(GL_TEXTURE_2D, source1->GetBufferTextureID());
		}

		for (std::vector<CachedRenderBatch>::iterator batchesIter = m_cachedRenderBatches[passIter->m_geometryType].begin(); batchesIter != m_cachedRenderBatches[passIter->m_geometryType].end(); ++batchesIter) {
			state->CalculateShaderState(batchesIter->m_renderParameters, batchesIter->m_renderBatch.m_effectParameters);

			if (batchesIter->m_renderBatch.m_effectParameters.m_twoSided)
				glDisable(GL_CULL_FACE);
			else
				glEnable(GL_CULL_FACE);

			state->b_useDiffuseTexture = m_textureManager->SetTexture(e_TextureChannelDiffuse, batchesIter->m_renderBatch.m_effectParameters.m_diffuseTexture);
			state->b_useEnvironmentMap = m_textureManager->SetTexture(e_TextureChannelEnvMap, batchesIter->m_renderParameters.m_environmentMap);
			state->b_useNormalMap = m_textureManager->SetTexture(e_TextureChannelNormalMap, batchesIter->m_renderBatch.m_effectParameters.m_normalMap);

			state->SetAttributeLocation(m_geometryManager->GetAttributeLocation(batchesIter->m_renderBatch.m_geometryID, batchesIter->m_renderBatch.m_effectParameters.m_animationTime));
			shader->SetShaderState(state);

			m_geometryManager->RenderGeometry(batchesIter->m_renderBatch.m_geometryID);
		}

		delete state;
	}
	
	glutSwapBuffers();
}

const FrameBufferTexture* GraphicsManager::GetFrameBufferTexture (const std::string& frameBufferTextureName) {
	std::map<std::string, FrameBufferTexture*>::iterator iter = m_frameBufferTextures.find(frameBufferTextureName);

	if (iter == m_frameBufferTextures.end())
		return NULL;
	else
		return iter->second;
}
