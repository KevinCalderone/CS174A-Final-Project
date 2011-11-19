#ifndef __GRAPHICSSETTINGS_H__
#define __GRAPHICSSETTINGS_H__

const unsigned int c_window_width = 800;
const unsigned int c_window_height = 600;

const unsigned int c_num_point_lights = 3;		// must be same value in shaders

const float c_num_falloff_range = 0.0001f;		// must be greater than 0

enum TextureType { e_TextureType2d = GL_TEXTURE_2D, e_TextureTypeCube = GL_TEXTURE_CUBE_MAP };

enum TextureChannel { 
	// Object Defined Shaders
	e_TextureChannelDiffuse = GL_TEXTURE0, 
	e_TextureChannelEnvMap = GL_TEXTURE1, 
	e_TextureChannelNormalMap = GL_TEXTURE2, 

	// Pipeline Defined Shaders
	e_TextureChannelRenderPassSource0 = GL_TEXTURE3,
	e_TextureChannelRenderPassSource1 = GL_TEXTURE4,

	e_TextureChannelFirst = GL_TEXTURE0
};

enum TextureMode { e_TextureModeNearest, e_TextureModeBiLinear, e_TextureModeTriLinear };

enum TextureFormat { e_TextureFormatRGB = GL_BGR, e_TextureFormatRGBA = GL_BGRA };

#endif