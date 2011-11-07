#include "GraphicsManager.h"

#include <fstream>

#include "UberShader.h"
#include "GeometryManager.h"
#include "TextureManager.h"

#include "EffectParameters.h"
#include "RenderParameters.h"

#include "RenderBatch.h"
#include "ShaderState.h"
#include "Geometry.h"

GraphicsManager::GraphicsManager (const std::string& assetLibrary) 
	: m_uberShader(NULL), m_geometryManager(NULL), m_textureManager(NULL), m_assetLibrary(assetLibrary)
{
	ReloadAssets();

	glEnable(GL_DEPTH_TEST);
}

GraphicsManager::~GraphicsManager () {
	ClearAssets();
}

void GraphicsManager::ClearAssets () {
	if (m_uberShader != NULL) {
		delete m_uberShader;
		m_uberShader = NULL;
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
		std::string vertexShaderFile;
		std::string fragmentShaderFile;
		std::string geometryLibrary;
		std::string textureLibrary;
   
		is >> vertexShaderFile;
		is >> fragmentShaderFile;
		is >> geometryLibrary;
		is >> textureLibrary;

		m_geometryManager = new GeometryManager(geometryLibrary);
		m_uberShader = new UberShader(vertexShaderFile, fragmentShaderFile);
		m_textureManager = new TextureManager(textureLibrary);

		is.close();
   }           
}

void GraphicsManager::ClearScreen () {
	glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsManager::SetRenderParameters(const RenderParameters& renderParameters) {
	m_renderParameters = renderParameters;
}

void GraphicsManager::Render (const RenderBatch& batch) {
	if (m_uberShader == NULL)
		return;


	ShaderState state = CalculateShaderState(batch.m_effectParameters);
	m_uberShader->SetShaderState(state);
	m_textureManager->SetTexture(e_TextureChannelDiffuse, batch.m_effectParameters.m_diffuseTexture);
	m_textureManager->SetTexture(e_TextureChannelEnvMap, m_renderParameters.m_environmentMap);

	m_geometryManager->RenderGeometry(batch.m_geometryID);
}

void GraphicsManager::SwapBuffers () {
	glutSwapBuffers();
}

ShaderState GraphicsManager::CalculateShaderState (const EffectParameters& effectParameters) {
	ShaderState state;

	state.m_projectionMatrix = m_renderParameters.m_projectionMatrix;
	state.m_modelviewMatrix = effectParameters.m_modelviewMatrix;

	state.b_useDiffuseTexture = m_textureManager->HasTexture(effectParameters.m_diffuseTexture);
	state.b_useEnvironmentMap = m_textureManager->HasTexture(m_renderParameters.m_environmentMap);

	state.m_eyePosition = m_renderParameters.m_eyePosition;

	state.m_lightDirection = m_renderParameters.m_lightDirection;
	state.m_lightCombinedAmbient = m_renderParameters.m_lightAmbient * effectParameters.m_materialDiffuse;
	state.m_lightCombinedDiffuse = m_renderParameters.m_lightDiffuse * effectParameters.m_materialDiffuse;
	state.m_lightCombinedSpecular = m_renderParameters.m_lightSpecular * effectParameters.m_materialSpecular;
	state.m_materialSpecularExponent = effectParameters.m_materialSpecularExponent;

	return state;
}