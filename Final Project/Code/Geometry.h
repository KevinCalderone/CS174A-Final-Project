#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Angel.h"

enum GeometryMode { 
	e_GeometryModeTriangles = GL_TRIANGLES,
	e_GeometryModeTriangleStrip = GL_TRIANGLE_STRIP
};

struct Geometry
{
	GeometryMode m_geometryMode;

	GLuint m_vertexStart;
	GLuint m_numVertex;
};

#endif