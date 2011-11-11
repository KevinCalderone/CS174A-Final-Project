#ifndef __FRAMEBUFFERTEXTURE_H__
#define __FRAMEBUFFERTEXTURE_H__

#include <string>

#include "Angel.h"

class FrameBufferTexture
{
public:
	FrameBufferTexture (const std::string& format, unsigned int width, unsigned int height);
	~FrameBufferTexture ();

	GLuint GetBufferTextureID () const { return m_bufferTextureID; }

	unsigned int GetBufferTextureWidth () const { return m_bufferTextureWidth; }
	unsigned int GetBufferTextureHeight () const { return m_bufferTextureHeight; }

private:
	GLuint m_bufferTextureID;

	unsigned int m_bufferTextureWidth;
	unsigned int m_bufferTextureHeight;
};

#endif