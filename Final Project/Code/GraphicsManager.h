#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <string>

struct RenderBatch;
struct EffectState;

class UberShader;
class GeometryManager;
class TextureManager;

struct ShaderState;

class GraphicsManager
{
public:
	GraphicsManager (const std::string& assetLibrary);
	~GraphicsManager ();

	void ClearScreen ();
	void Render (const RenderBatch& batch);
	void SwapBuffers ();

	void ReloadAssets ();

private:
	void ClearAssets ();
	ShaderState CalculateShaderState (const EffectState& effectState);

	const std::string m_assetLibrary;

	UberShader* m_uberShader;
	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;
};

#endif