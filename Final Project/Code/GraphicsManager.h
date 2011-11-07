#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <string>

#include "RenderParameters.h"

struct RenderBatch;
struct EffectParameters;

class UberShader;
class GeometryManager;
class TextureManager;

struct ShaderState;

class GraphicsManager
{
public:
	GraphicsManager (const std::string& assetLibrary);
	~GraphicsManager ();

	void SetCameraProjection (vec3 playerPosition);
	void SetCameraOrthogonal ();

	void ClearScreen ();
	void SetRenderParameters (const RenderParameters& renderParameters);
	void Render (const RenderBatch& batch);
	void SwapBuffers ();

	void ReloadAssets ();

private:
	void ClearAssets ();
	ShaderState CalculateShaderState (const EffectParameters& effectParameters);

	const std::string m_assetLibrary;

	RenderParameters m_renderParameters;

	UberShader* m_uberShader;
	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;
};

#endif