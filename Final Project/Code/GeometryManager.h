#ifndef __GEOMETRYMANAGER_H__
#define __GEOMETRYMANAGER_H__

#include <map>

#include "Angel.h"

struct Vertex;
struct Geometry;
struct AttributeLocation;

class GeometryManager
{
public:
	GeometryManager (const std::string& assetFile);
	~GeometryManager ();

	AttributeLocation GetAttributeLocation (const std::string& geometryID, float animationTime);
	void RenderGeometry (const std::string& geometryID);

private:
	void InitBuffer (unsigned int size);

	Geometry* LoadOBJFile (const std::string& geometryFile);

	std::map<std::string, Geometry*> m_geometry;

	GLuint m_vao;
	GLuint m_buffer;
	unsigned int m_vertexDataUsed;
};

#endif