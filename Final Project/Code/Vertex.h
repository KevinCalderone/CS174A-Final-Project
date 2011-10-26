#ifndef __VERTEX_H__
#define __VERTEX_H__

// 32-byte aligned interleaved vertex data
struct Vertex
{
	vec3 position;
	vec3 normal;
//	float _padding;
};

const unsigned int c_positionDataOffset = 0;
const unsigned int c_normalDataOffset = sizeof(vec3);

#endif