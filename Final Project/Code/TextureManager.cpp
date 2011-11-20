#include "TextureManager.h"

#include <fstream>

#include "BMPTexture.h"

TextureManager::TextureManager (const std::string& assetLibrary) {
	std::ifstream is;
	is.open (assetLibrary.c_str(), std::ios::binary);

	if (!is.is_open()) {
		printf("TextureManager::TextureManager: Error opening asset library.\n");
	}
	else {
		while (is.good()) {
			std::string textureType;
			std::string textureFormatString;

			is >> textureType >> textureFormatString;
			
			TextureFormat textureFormat = e_TextureFormatRGB;
			if (textureFormatString == "rgb") {
				textureFormat = e_TextureFormatRGB;
			}
			else if (textureFormatString == "rgba") {
				textureFormat = e_TextureFormatRGBA;
			}

			std::vector<const std::string> textureFiles;

			if (textureType == "2d") {
				std::string textureName;
				std::string textureFile;

				is >> textureName;
				is >> textureFile;

				textureFiles.push_back(textureFile);

				LoadTextureFile(textureName, textureFormat, e_TextureType2d, e_TextureModeTriLinear, textureFiles);      
			}
			else if (textureType == "cube") {
				std::string textureName;
				is >> textureName;

				std::string textureFile;
				for (int i = 0; i < 6; ++i) {
					is >> textureFile;
					textureFiles.push_back(textureFile);
				}

				LoadTextureFile(textureName, textureFormat, e_TextureTypeCube, e_TextureModeBiLinear, textureFiles);      
			}
		}

		is.close();
	}   
}

TextureManager::~TextureManager () {
	for (std::map<std::string, BMPTexture*>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
		delete iter->second;
}

bool TextureManager::SetTexture (TextureChannel channel, const std::string& textureName) const {
	std::map<std::string, BMPTexture*>::const_iterator iter = m_textures.find(textureName);

	if (iter == m_textures.end()) 
		return false;

	iter->second->Apply(channel);
	return true;
}

bool TextureManager::IsTransparent (const std::string& textureName) const {
	std::map<std::string, BMPTexture*>::const_iterator iter = m_textures.find(textureName);

	if (iter == m_textures.end()) 
		return false;

	return iter->second->GetFormat() == e_TextureFormatRGBA;
}

void TextureManager::LoadTextureFile (const std::string& textureName, TextureFormat textureFormat, TextureType type, TextureMode mode, const std::vector<const std::string>& textureFiles) {
	std::map<std::string, BMPTexture*>::iterator iter = m_textures.find(textureName);

	if (iter != m_textures.end())
		return;

	m_textures[textureName] = new BMPTexture(type, mode, textureFormat, textureFiles);
}