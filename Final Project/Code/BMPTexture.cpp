#include "BMPTexture.h"

BMPTexture::BMPTexture (std::string fileName, TextureMode mode)
  : file(fileName), texture(0) 
{
       
  std::ifstream is;
  is.open (file.c_str(), std::ios::binary );

  if( !is.is_open() )
      printf("Error loading Texture");
  else{
       int length;
       char * data;
       
       is.seekg (0, std::ios::end);
       length = is.tellg();
       is.seekg (0, std::ios::beg);

       data = new char [length];

       is.read (data,length);
       is.close();

       LoadTexture(data, mode);
	  
	  delete [] data;
   }                       

}
                                   
BMPTexture::~BMPTexture(){

   glDeleteTextures(1,&texture);

}
 
void BMPTexture::LoadTexture (char* data, TextureMode mode) {
	unsigned int dataBegin = *((unsigned int*)(data+10)); 

	width = *((unsigned int*)(data+18));
	height = *((unsigned int*)(data+22));

	glGenTextures(1, &texture); 

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, &data[dataBegin]);

	if (mode == e_TextureModeNearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (mode == e_TextureModeLinear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_T);

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);	
}
 
void BMPTexture::Apply () {
	glBindTexture(GL_TEXTURE_2D, texture); 
}
