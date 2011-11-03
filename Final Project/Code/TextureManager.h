#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <string>
#include <map>

#include "Angel.h"

class BMPTexture;

class TextureManager
{
public:
	TextureManager (const std::string& assetLibrary);
	~TextureManager ();

	void SetTexture (const std::string& textureName);
	bool HasTexture (const std::string& textureName);

private:
	void LoadTextureFile (const std::string& textureName, const std::string& textureFile);

	std::map<std::string, BMPTexture*> m_textures;
};

#endif