#ifndef __BMPTEXTURE_H__
#define __BMPTEXTURE_H__

#include <string>
#include <vector>
#include <fstream>

#include "Angel.h"

enum TextureType { e_TextureType2d = GL_TEXTURE_2D, e_TextureTypeCube = GL_TEXTURE_CUBE_MAP };
enum TextureChannel { e_TextureChannelDiffuse = GL_TEXTURE0, e_TextureChannelEnvMap = GL_TEXTURE1, e_TextureChannelNormalMap = GL_TEXTURE2 };
enum TextureMode { e_TextureModeNearest, e_TextureModeBiLinear, e_TextureModeTriLinear };

class BMPTexture
{
public:
	BMPTexture (TextureType type, TextureMode mode, const std::vector<const std::string>& fileNames);
	~BMPTexture (); 

	void Apply (TextureChannel channel);
	
private:
     
    char* ReadTextureFile (const std::string& fileName);
	void Load2dTexture (const std::vector<const std::string>& fileNames);
    void LoadCubeTexture (const std::vector<const std::string>& fileNames);

	std::string file;
     
	TextureType m_type;
	GLuint m_textureID;
};

#endif