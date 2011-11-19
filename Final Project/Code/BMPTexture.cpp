#include "BMPTexture.h"

BMPTexture::BMPTexture (TextureType type, TextureMode mode, TextureFormat format, const std::vector<const std::string>& fileNames)
  : m_type(type), m_format(format), m_textureID(0) 
{

	switch (type) {
		case e_TextureType2d:
			Load2dTexture(fileNames);	 
		break;

		case e_TextureTypeCube:
			LoadCubeTexture(fileNames);
		break;
	}

	if (mode == e_TextureModeNearest) {
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (mode == e_TextureModeBiLinear) {
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (mode == e_TextureModeTriLinear) {
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(m_type);
	}                    
}
                                   
BMPTexture::~BMPTexture() {
	glDeleteTextures(1, &m_textureID);
}

char* BMPTexture::ReadTextureFile (const std::string& fileName) {
	std::ifstream is;
	is.open (fileName.c_str(), std::ios::binary);

	if( !is.is_open() ) {
		printf("BMPTexture::ReadTextureFile: Error loading Texture %s", fileName.c_str());
		return NULL;
	}

	int length;
	char* data;

	is.seekg (0, std::ios::end);
	length = is.tellg();
	is.seekg (0, std::ios::beg);

	data = new char [length];

	is.read (data,length);
	is.close();

	return data;
}

void BMPTexture::Load2dTexture (const std::vector<const std::string>& fileNames) {
	if (fileNames.size() != 1)
		return;

	char* data = ReadTextureFile(fileNames[0]);

	if (data == NULL)
		return;
	
	unsigned int dataBegin = *((unsigned int*)(data+10)); 

	unsigned int width = *((unsigned int*)(data+18));
	unsigned int height = *((unsigned int*)(data+22));

	glGenTextures(1, &m_textureID); 

	glBindTexture(m_type, m_textureID);
	glTexImage2D(m_type, 0, 4, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[dataBegin]);

	delete[] data;
}

void BMPTexture::LoadCubeTexture (const std::vector<const std::string>& fileNames) {
	if (fileNames.size() != 6)
		return;

	bool error = false;
	char* data[6];

	for (int i = 0; i < 6; ++i) {
		data[i] = ReadTextureFile(fileNames[i]);
		error = error || data[i] == NULL;
	}

	if (error) {
		for (int i = 0; i < 6; ++i) {
			if (data[i] != NULL)
				delete[] data[i];
		}

		printf("BMPTexture::LoadCubeTexture: Error loading Texture");
		return;
	}
	
	glGenTextures(1, &m_textureID); 
	glBindTexture(m_type, m_textureID);

	static const GLuint textureFaces[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	for (int i = 0; i < 6; ++i) {
		unsigned int dataBegin = *((unsigned int*)(data[i]+10)); 
		unsigned int width = *((unsigned int*)(data[i]+18));
		unsigned int height = *((unsigned int*)(data[i]+22));

		glTexImage2D(textureFaces[i], 0, 4, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[i][dataBegin]);
		delete[] data[i];
	}
}
 
void BMPTexture::Apply (TextureChannel channel) {
	glActiveTexture(channel);
	glBindTexture(m_type, m_textureID); 
}
