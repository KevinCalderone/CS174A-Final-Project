#include "GeometryManager.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Vertex.h"
#include "Geometry.h"

GeometryManager::GeometryManager (const std::string& assetFile) 
	: m_vertexDataUsed(0)
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
			LoadOBJFile(geometryName, geometryFile);      
		}

		is.close();
	}   
}

GeometryManager::~GeometryManager () {
	for (std::map<std::string, Geometry*>::iterator iter = m_geometry.begin(); iter != m_geometry.end(); ++iter) 
		delete iter->second;
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
    
	m_vertexDataUsed = 0;
}

void GeometryManager::RenderGeometry (const std::string& geometryID) {
	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter == m_geometry.end())
		return;
	
	Geometry* geometry = iter->second;
	glDrawArrays(geometry->m_geometryMode, geometry->m_vertexStart, geometry->m_numVertex);
}

static void TokenizeString (const std::string& input, const std::string& delims, std::vector<std::string>& tokens) {
    tokens.clear();

    std::string::size_type beg_index, end_index;

    beg_index = input.find_first_not_of(delims);

    while (beg_index != std::string::npos) {
        end_index = input.find_first_of(delims, beg_index);
        
		if (end_index == std::string::npos) 
			end_index = input.length();

        tokens.push_back(input.substr(beg_index, end_index - beg_index));
        beg_index = input.find_first_not_of(delims,end_index);
    }
}

template <typename T>
static T ConvertString (const std::string& string) {
	std::stringstream ss(string);
	T result;
	return ss >> result ? result : 0;
}

void GeometryManager::LoadOBJFile (const std::string& geometryID, const std::string& geometryFile) {
	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter != m_geometry.end())
		return;

	std::ifstream is;
	is.open (geometryFile.c_str(), std::ios::binary);

	if (!is.is_open()) {
		printf("GeometryManager::LoadOBJFile: Error loading file %s.\n", geometryFile.c_str());
		return;
	}
	
	std::vector<std::string> tokens;
	std::string fileLine;

	std::vector<Vertex> geometryData;

	std::vector<vec3> vertexes;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;

	 while (!is.eof()) {
	    getline(is, fileLine);
	    TokenizeString(fileLine, " /", tokens);

		if (tokens.size() == 0)
			continue;

		if (tokens[0] == "v" && tokens.size() == 4) {
			vertexes.push_back(vec3(ConvertString<float>(tokens[1]), ConvertString<float>(tokens[2]), ConvertString<float>(tokens[3])));
		}
		else if (tokens[0] == "vn" && tokens.size() == 4) {
			normals.push_back(vec3(ConvertString<float>(tokens[1]), ConvertString<float>(tokens[2]), ConvertString<float>(tokens[3])));
		}
		else if (tokens[0] == "vt" && tokens.size() > 2) {
			texCoords.push_back(vec2(ConvertString<float>(tokens[1]), ConvertString<float>(tokens[2])));
		}
		else if (tokens[0] == "f" && tokens.size() == 10) {
			bool invalid = false;

			unsigned int v1, vt1, vn1;
			v1 = ConvertString<int>(tokens[1]) - 1;
			invalid |= v1 >= vertexes.size();
			vt1 = ConvertString<int>(tokens[2]) - 1;
			invalid |= vt1 >= texCoords.size();
			vn1 = ConvertString<int>(tokens[3]) - 1;
			invalid |= vn1 >= normals.size();

			unsigned int v2, vt2, vn2;
			v2 = ConvertString<int>(tokens[4]) - 1;
			invalid |= v2 >= vertexes.size();
			vt2 = ConvertString<int>(tokens[5]) - 1;
			invalid |= vt2 >= texCoords.size();
			vn2 = ConvertString<int>(tokens[6]) - 1;
			invalid |= vn2 >= normals.size();

			unsigned int v3, vt3, vn3;
			v3 = ConvertString<int>(tokens[7]) - 1;
			invalid |= v3 >= vertexes.size();
			vt3 = ConvertString<int>(tokens[8]) - 1;
			invalid |= vt3 >= texCoords.size();
			vn3 = ConvertString<int>(tokens[9]) - 1;
			invalid |= vn3 >= normals.size();

			if (invalid) {
				printf("GeometryManager::LoadOBJFile: Invalid triangle\n");
				continue;
			}

			geometryData.push_back(Vertex(vertexes[v1], normals[vn1], texCoords[vt1]));
			geometryData.push_back(Vertex(vertexes[v2], normals[vn2], texCoords[vt2]));
			geometryData.push_back(Vertex(vertexes[v3], normals[vn3], texCoords[vt3]));
		}
	}
	
	int dataSize = geometryData.size() * sizeof(Vertex);

	if (dataSize == 0)
		return;

	glBufferSubData(GL_ARRAY_BUFFER, m_vertexDataUsed, dataSize, &geometryData[0]);

	Geometry* geometry = new Geometry();
	geometry->m_geometryMode = e_GeometryModeTriangles;
	geometry->m_numVertex = dataSize / sizeof(Vertex);
	geometry->m_vertexStart = m_vertexDataUsed / sizeof(Vertex);;

	m_geometry[geometryID] = geometry;

	m_vertexDataUsed += dataSize;
}