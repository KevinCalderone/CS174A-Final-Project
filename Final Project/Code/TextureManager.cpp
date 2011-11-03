#include "TextureManager.h"

#include <fstream>
#include <string>

#include "BMPTexture.h"

TextureManager::TextureManager (const std::string& assetLibrary) {
	std::ifstream is;
	is.open (assetLibrary.c_str(), std::ios::binary);

	if (!is.is_open()) {
		printf("TextureManager::TextureManager: Error opening asset library.\n");
	}
	else {
		std::string textureName;
		std::string textureFile;
       
		while (is.good()) {
			is >> textureName;
			is >> textureFile;           
			LoadTextureFile(textureName, textureFile);      
		}

		is.close();
	}   
}

TextureManager::~TextureManager () {
	for (std::map<std::string, BMPTexture*>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
		delete iter->second;
}

void TextureManager::SetTexture (const std::string& textureName) {
	std::map<std::string, BMPTexture*>::iterator iter = m_textures.find(textureName);

	if (iter == m_textures.end()) 
		return;

	glEnable(GL_TEXTURE_2D);
	iter->second->Apply();
}

bool TextureManager::HasTexture (const std::string& textureName) {
	return m_textures.find(textureName) != m_textures.end();
}

void TextureManager::LoadTextureFile (const std::string& textureName, const std::string& textureFile) {
	std::map<std::string, BMPTexture*>::iterator iter = m_textures.find(textureName);

	if (iter != m_textures.end())
		return;

	m_textures[textureName] = new BMPTexture(textureFile, e_TextureModeLinear);
}