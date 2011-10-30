#ifndef __BMPTEXTURE_H__
#define __BMPTEXTURE_H__

#include <string>
#include <fstream>

#include "Angel.h"

enum TextureMode { e_TextureModeNearest, e_TextureModeLinear };

class BMPTexture
{
public:
	BMPTexture (std::string fileName, TextureMode mode);
	~BMPTexture (); 

	void Apply ();

	int GetWidth () { return width; }
    int GetHeight () { return height; }   
	
private:
     
	void LoadTexture (char* data, TextureMode mode);
        
	std::string file;
     
	GLuint texture;
	unsigned int width;
	unsigned int height;
  
};

#endif