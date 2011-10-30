#include "GraphicsManager.h"

#include "UberShader.h"
#include "GeometryManager.h"
#include "TextureManager.h"

GraphicsManager::GraphicsManager (const std::string& assetFile) 
	: m_uberShader(NULL), m_geometryManager(NULL), m_textureManager(NULL)
{

}

GraphicsManager::~GraphicsManager () {
	if (m_uberShader != NULL)
		delete m_uberShader;

	if (m_geometryManager != NULL)
		delete m_geometryManager;
	
	if (m_textureManager != NULL)
		delete m_textureManager;
}

void GraphicsManager::ClearScreen () {

}

void GraphicsManager::Render (const RenderBatch& batch) {

}

void GraphicsManager::SwapBuffers () {

}