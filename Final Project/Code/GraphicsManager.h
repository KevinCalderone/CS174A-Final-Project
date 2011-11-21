#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <map>
#include <vector>
#include <string>

#include "RenderParameters.h"

struct RenderBatch;
struct CachedRenderBatch;
struct EffectParameters;

class ForwardShader;
class PostProcessShader;
class GeometryManager;
class TextureManager;

class FrameBufferTexture;
struct RenderPass;

struct ForwardShaderState;
struct PostProcessShaderState;

/*
Kevin TODO

ON DECK
- Assign constants from GraphicsSettings into shaders
- Pass blur widths into post process shader 
- Make render passes and frame buffer textures const
- Optimization: Reduce Gausian sampling taps depending on how much color bleed we end up wanting

FUTURE FEATURES
- Expose more options in RenderParameters such as DOF
- Optimization: Only send diff of state to GPU
- Add dynamic geometry
	- Add particles for a torch
- Add gloss maps
- Optimization: Combine final pipeline into MRT passes to reduce total passes
*/

class GraphicsManager
{
public:
	GraphicsManager (const std::string& assetLibrary);
	~GraphicsManager ();

	void ClearScreen ();
	void Render (const RenderBatch& batch);
	void SwapBuffers ();

	void ReloadAssets ();

	RenderParameters& GetRenderParameters () { return m_renderParameters; }

private:
	void ClearAssets ();
	void LoadEffectFile (const std::string& effectFile);

	const FrameBufferTexture* GetFrameBufferTexture (const std::string& frameBufferTextureName);

	const std::string m_assetLibrary;

	RenderParameters m_renderParameters;

	ForwardShader* m_forwardShader;
	PostProcessShader* m_postProcessShader;
	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;

	std::vector<CachedRenderBatch> m_cachedRenderBatches[e_GeometryTypeCount];

	std::map<std::string, FrameBufferTexture*> m_frameBufferTextures;
	std::vector<RenderPass> m_renderPasses;

	GLuint m_fbo;
};

#endif