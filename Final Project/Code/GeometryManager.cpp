#include "GeometryManager.h"

#include <fstream>
#include <string>

#include "Vertex.h"
#include "Geometry.h"

GeometryManager::GeometryManager (const std::string& assetFile) 
	: m_vertexData(NULL), m_vertexDataUsed(0)
{
	std::ifstream is;
	is.open (assetFile.c_str(), std::ios::binary);

	if (!is.is_open()) {
		printf("GeometryManager::GeometryManager: Error opening asset library.\n");
	}
	else {
		unsigned int bufferSize;
		is >> bufferSize;

		InitBuffer(bufferSize);

		std::string geometryFile;
		std::string geometryName;

		while (is.good()) {
			is >> geometryName;      
			is >> geometryFile;
			LoadGeometryFile(geometryName, geometryFile);      
		}

		is.close();
	}   
}

GeometryManager::~GeometryManager () {
	for (std::map<std::string, Geometry*>::iterator iter = m_geometry.begin(); iter != m_geometry.end(); ++iter) 
		delete iter->second;

	if (m_vertexData != NULL)
		delete m_vertexData;
}

void GeometryManager::InitBuffer (unsigned int size) {
	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &m_buffer );
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), NULL, GL_STATIC_DRAW);
    
	m_vertexData = new Vertex[size];
	m_vertexDataUsed = 0;
}

void GeometryManager::RenderGeometry (const std::string& geometryID) {
	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter == m_geometry.end())
		return;
	
	Geometry* geometry = iter->second;
	glDrawArrays(geometry->m_geometryType, geometry->m_vertexStart, geometry->m_numVertex);
}

void GeometryManager::LoadGeometryFile (const std::string& geometryID, const std::string& geometryFile) {
	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter != m_geometry.end())
		return;
	
	// Not done yet, so just manually load in a cube for now
	static const unsigned int c_numBoxVertexes = 14;
	static const unsigned int c_sizeBoxData = c_numBoxVertexes * 8;
	static const float c_boxData[c_sizeBoxData] = {
		// Cube
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 0.0f,

		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, 1.0f,

		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 0.0f,

		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		0.0f, 1.0f,
		
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 0.0f,
	
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f,
			
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f
	};

	glBufferSubData(GL_ARRAY_BUFFER, m_vertexDataUsed, c_sizeBoxData * sizeof(float), &c_boxData[0]);

	Geometry* geometry = new Geometry();
	geometry->m_geometryType = e_GeometryTypeTriangleStrip;
	geometry->m_numVertex = c_numBoxVertexes;
	geometry->m_vertexStart = m_vertexDataUsed;

	m_geometry[geometryID] = geometry;

	m_vertexDataUsed += c_numBoxVertexes;
}