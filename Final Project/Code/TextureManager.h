#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <string>
#include <map>

class BMPTexture;

class TextureManager
{
public:
	TextureManager ();
	~TextureManager ();

private:
	std::map<std::string, BMPTexture*> m_textures;
};

#endif