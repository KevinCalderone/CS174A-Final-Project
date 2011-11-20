#ifndef __BMPTEXTURE_H__
#define __BMPTEXTURE_H__

#include <string>
#include <vector>
#include <fstream>

#include "Angel.h"

#include "GraphicsSettings.h"

class BMPTexture
{
public:
	BMPTexture (TextureType type, TextureMode mode, TextureFormat format, const std::vector<const std::string>& fileNames);
	~BMPTexture (); 

	void Apply (TextureChannel channel);
	TextureFormat GetFormat () { return m_format; }

private:
     
    char* ReadTextureFile (const std::string& fileName);
	void Load2dTexture (const std::vector<const std::string>& fileNames);
    void LoadCubeTexture (const std::vector<const std::string>& fileNames);

	std::string file;
     
	TextureType m_type;
	TextureFormat m_format;
	GLuint m_textureID;
};

#endif