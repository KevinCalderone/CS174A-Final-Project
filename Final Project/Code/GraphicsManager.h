#ifndef __GRAPHICSMANAGER_H__
#define __GRAPHICSMANAGER_H__

#include <string>

struct RenderBatch;
struct EffectState;

class UberShader;
class GeometryManager;
class TextureManager;

class GraphicsManager
{
public:
	GraphicsManager (const std::string& assetFile);
	~GraphicsManager ();

	void ClearScreen ();
	void Render (const RenderBatch& batch);
	void SwapBuffers ();

private:
	UberShader* m_uberShader;

	GeometryManager* m_geometryManager;
	TextureManager* m_textureManager;
};

#endif