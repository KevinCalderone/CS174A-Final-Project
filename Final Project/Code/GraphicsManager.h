#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <string>

#include "RenderParameters.h"

struct RenderBatch;
struct EffectParameters;

class ForwardShader;
class PostProcessShader;
class GeometryManager;
class TextureManager;

struct ShaderState;

/*
Kevin TODO

INTERNAL STUFF
- Make sure everything is gettings released in the destructors
- Abstract render passes so it is no longer hard coded
- Add a shader state class for PostProcessShader
- Add a texture class for frame buffer textures
- Only send diff of state to GPU

FEATURES
- Add access to depth buffer in post process stage
- Expose more options in RenderParameters such as DOF
- Cache RenderBatches to allow multipass effects
- Add some kind of shadows, probably point light shadows
- Add transparency option in EffectParameters
- Add dynamic geometry
	- Add particles for a torch
	- Add some kind of animation
- Add gloss maps
- Add SSAO
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
	void InitRenderBuffers ();

	ShaderState CalculateShaderState (const EffectParameters& effectParameters);

	const std::string m_assetLibrary;

	RenderParameters m_renderParameters;

	ForwardShader* m_forwardShader;
	PostProcessShader* m_postProcessShader;
	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;

	GLuint m_fbo;
	GLuint m_fboDepth;
	GLuint m_fboColor;
	GLuint m_fboColorHalf;
	GLuint m_fboColorBlurX;
	GLuint m_fboColorBlurXY;
};

#endif