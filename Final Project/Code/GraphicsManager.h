#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <map>
#include <vector>
#include <string>

#include "RenderParameters.h"

struct RenderBatch;
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
- Make sure everything is gettings released in the destructors
- Refactoring: Abstract render passes so it is no longer hard coded
	- Add a shader state class for PostProcessShader
	- Add a texture class for frame buffer textures
- Handle depth test as a parameter
- Add cubemap shadowmapping for point light shadows
- Add skeletal animation	
	- Change model file format to one that supports blend weights
	- Try to find models/figure out how to make animations in blender
- Assign constants from GraphicsSettings into shaders
- Remove dependency to "ScreenQuad" geometry name
- ShadeState doesn't seem properly abstracted
- Double check I am turning depth testing on/off correctly
- Pass blur widths into post process shader 
- Make render passes and frame buffer textures const

FUTURE FEATURES
- Add access to depth buffer in post process stage
- Expose more options in RenderParameters such as DOF
- Optimization: Only send diff of state to GPU
- Optimization: Figure out if blitting or generateMipMaps if faster for downsampleing
- Add transparency option in EffectParameters
- Add dynamic geometry
	- Add particles for a torch
	- Add some kind of animation
- Add gloss maps
- Cache RenderBatches to allow multipass effects
- Add SSAO
- Optimization: Combine final pipeline into MRT passes to reduce total passes
- Optimization: Use minimal texture formats(eg. get rid of alpha channel I am not using everywhere)
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
	void InitRenderBuffers ();

	ForwardShaderState CalculateForwardShaderState (const EffectParameters& effectParameters);
	PostProcessShaderState CalculatePostProcessShaderState (const EffectParameters& effectParameters);

	const FrameBufferTexture* GetFrameBufferTexture (const std::string& frameBufferTextureName);

	const std::string m_assetLibrary;

	RenderParameters m_renderParameters;

	ForwardShader* m_forwardShader;
	PostProcessShader* m_postProcessShader;
	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;

	std::vector<RenderBatch> m_renderBatches;

	std::map<std::string, FrameBufferTexture*> m_frameBufferTextures;
	std::vector<RenderPass> m_renderPasses;

	GLuint m_fbo;
	GLuint m_fboDepth;
	GLuint m_fboColor;
	GLuint m_fboColorHalf;
	GLuint m_fboColorBlurX;
	GLuint m_fboColorBlurXY;
};

#endif