#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Angel.h"

enum GeometryType { 
	e_GeometryTypeTriangles = GL_TRIANGLES,
	e_GeometryTypeTriangleStrip = GL_TRIANGLE_STRIP
};

struct Geometry
{
	GeometryType m_geometryType;

	GLuint m_vertexStart;
	GLuint m_numVertex;
};

#endif