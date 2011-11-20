#ifndef __ATTRIBUTELOCATION__
#define __ATTRIBUTELOCATION__

struct AttributeLocation
{
	AttributeLocation () 
		: m_animatedGeometry(0), m_position0(0), m_normal0(0), m_texCoord0(0), m_position1(0) ,m_normal1(0), m_texCoord1(0)
	{}

	bool m_animatedGeometry;

	GLuint m_position0;
	GLuint m_normal0;
	GLuint m_texCoord0;

	GLuint m_position1;
	GLuint m_normal1;
	GLuint m_texCoord1;
};

#endif