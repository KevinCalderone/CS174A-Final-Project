#ifndef __GEOMETRYMANAGER_H__
#define __GEOMETRYMANAGER_H__

#include <map>

#include "Angel.h"

struct Vertex;
struct Geometry;

class GeometryManager
{
public:
	GeometryManager (const std::string& assetFile);
	~GeometryManager ();

	void RenderGeometry (const std::string& geometryID);

private:
	void InitBuffer (unsigned int size);

	void LoadOBJFile (const std::string& geometryID, const std::string& geometryFile);

	std::map<std::string, Geometry*> m_geometry;

	GLuint m_vao;
	GLuint m_buffer;
	unsigned int m_vertexDataUsed;
};

#endif