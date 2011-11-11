#include "FrameBufferTexture.h"

FrameBufferTexture::FrameBufferTexture (const std::string& format, unsigned int width, unsigned int height) 
	: m_bufferTextureWidth(width), m_bufferTextureHeight(height)
{
	GLuint textureFormat;
	GLuint pixelFormat;

	if (format == "DEPTHCOMPONENT") {
		textureFormat = GL_DEPTH_COMPONENT;
		pixelFormat = GL_DEPTH_COMPONENT;
	}
	else if (format == "RGBA16F") {
		textureFormat = GL_RGBA16F;
		pixelFormat = GL_RGBA;
	}
	else {
		printf("FrameBufferTexture::FrameBufferTexture: Invalid texture format %s.\n", format.c_str());
		system("PAUSE");
		exit(0);
	}

	glGenTextures(1, &m_bufferTextureID); 
	glBindTexture(GL_TEXTURE_2D, m_bufferTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

FrameBufferTexture::~FrameBufferTexture () {

}