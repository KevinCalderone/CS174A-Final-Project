#include "GeometryManager.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Vertex.h"
#include "Geometry.h"
#include "AttributeLocation.h"

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

		while (is.good()) {
			std::string geometryMode;

			is >> geometryMode;   

			if (geometryMode == "static") {
				std::string geometryFile;
				std::string geometryName;

				is >> geometryName;
				is >> geometryFile;

				Geometry* geometry = LoadOBJFile(geometryFile);  

				if (geometry != NULL)
					m_geometry[geometryName] = geometry;
			}
			else if (geometryMode == "keyframe") {					
				unsigned int fileCount;
				std::string geometryName;

				is >> fileCount;
				is >> geometryName;

				Geometry* keyframeGeometry = NULL;

				while (fileCount--) {
					std::string geometryFile;

					is >> geometryFile;

					Geometry* geometry = LoadOBJFile(geometryFile);  

					if (geometry == NULL) {
						continue;
					}
					else if (keyframeGeometry == NULL) {
						keyframeGeometry = geometry;
					}
					else {
						if (geometry->m_geometryMode != keyframeGeometry->m_geometryMode || geometry->m_numVertex != keyframeGeometry->m_numVertex) 
							printf("GeometryManager::GeometryManager: Incompatible keyframe file %s.\n", geometryFile);
						else 
							keyframeGeometry->m_vertexDataStarts.push_back(geometry->m_vertexDataStarts.back());
						
						delete geometry;
					}
				}

				if (keyframeGeometry != NULL)
					m_geometry[geometryName] = keyframeGeometry;
			}
		}

		is.close();
	}   
}

GeometryManager::~GeometryManager () {
	glDeleteBuffers(1, &m_buffer);
	glDeleteVertexArrays(1, &m_vao);

	for (std::map<std::string, Geometry*>::iterator iter = m_geometry.begin(); iter != m_geometry.end(); ++iter) 
		delete iter->second;
}

void GeometryManager::InitBuffer (unsigned int size) {
	// Create a vertex array object
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray( m_vao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &m_buffer );
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), NULL, GL_STATIC_DRAW);
    
	m_vertexDataUsed = 0;
}

AttributeLocation GeometryManager::GetAttributeLocation (const std::string& geometryID, float animationTime) {
	AttributeLocation attributeLocation;

	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter == m_geometry.end()) {
		printf("GeometryManager::GetAttributeLocation: Unknown geometryID %s.\n", geometryID.c_str());
	}
	else {
		Geometry* geometry = iter->second;

		unsigned int numAnimationModels = geometry->m_vertexDataStarts.size();

		unsigned int firstModel = (unsigned int)fmod(animationTime, numAnimationModels);
		unsigned int secondModel = (firstModel + 1) % numAnimationModels;

		if (firstModel >= numAnimationModels || secondModel >= numAnimationModels) {
			printf("GeometryManager::GetAttributeLocation: Invalid model indexes.\n");
			return attributeLocation;
		}

		unsigned int firstModelVertexStart = geometry->m_vertexDataStarts[firstModel];
		unsigned int secondModelVertexStart = geometry->m_vertexDataStarts[secondModel];

		attributeLocation.m_position0 = firstModelVertexStart + c_positionDataOffset;
		attributeLocation.m_normal0 = firstModelVertexStart + c_normalDataOffset;
		attributeLocation.m_texCoord0 = firstModelVertexStart + c_texCoord0DataOffset;

		attributeLocation.m_position1 = secondModelVertexStart + c_positionDataOffset;
		attributeLocation.m_normal1 = secondModelVertexStart + c_normalDataOffset;
		attributeLocation.m_texCoord1 = secondModelVertexStart + c_texCoord0DataOffset;

		attributeLocation.m_animatedGeometry = firstModel != secondModel;
	}

	return attributeLocation;
}

void GeometryManager::RenderGeometry (const std::string& geometryID) {
	std::map<std::string, Geometry*>::iterator iter = m_geometry.find(geometryID);

	if (iter == m_geometry.end()) {
		printf("GeometryManager::RenderGeometry: Unknown geometryID %s.\n", geometryID.c_str());
		return;
	}

	Geometry* geometry = iter->second;
	glDrawArrays(geometry->m_geometryMode, 0, geometry->m_numVertex);
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

Geometry* GeometryManager::LoadOBJFile (const std::string& geometryFile) {
	std::ifstream is;
	is.open (geometryFile.c_str(), std::ios::binary);

	if (!is.is_open()) {
		printf("GeometryManager::LoadOBJFile: Error loading file %s.\n", geometryFile.c_str());
		return NULL;
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

	if (dataSize == 0) {
		printf("GeometryManager::LoadOBJFile: Empty model file %s\n", geometryFile.c_str());
		return NULL;
	}

	glBufferSubData(GL_ARRAY_BUFFER, m_vertexDataUsed, dataSize, &geometryData[0]);

	GLenum error = glGetError();
	if (error) {
		std::cout << error;
		return NULL;
	}

	Geometry* geometry = new Geometry();
	geometry->m_geometryMode = e_GeometryModeTriangles;
	geometry->m_numVertex = dataSize / sizeof(Vertex);
	geometry->m_vertexDataStarts.push_back(m_vertexDataUsed);

	m_vertexDataUsed += dataSize;

	return geometry;
}