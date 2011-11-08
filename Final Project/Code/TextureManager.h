#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <string>
#include <vector>
#include <map>

#include "Angel.h"

#include "BMPTexture.h"

class TextureManager
{
public:
	TextureManager (const std::string& assetLibrary);
	~TextureManager ();

	void SetTexture (TextureChannel channel, const std::string& textureName);
	bool HasTexture (const std::string& textureName);

private:
	void LoadTextureFile (const std::string& textureName, TextureType type, TextureMode mode, const std::vector<const std::string>& textureFiles);

	std::map<std::string, BMPTexture*> m_textures;
};

#endif