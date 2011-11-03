#ifndef __VERTEX_H__
#define __VERTEX_H__

// 32-byte aligned interleaved data
struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texCoord0;
};

const unsigned int c_positionDataOffset = 0;
const unsigned int c_normalDataOffset = sizeof(vec3);
const unsigned int c_texCoord0DataOffset = 2 * sizeof(vec3);

#endif