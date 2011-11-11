#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__
#include "Angel.h"
#include "vec.h"

class BoundingBox
{
public:
	BoundingBox(vec2& center, float hw, float hl);
	~BoundingBox();
	vec2 calc(vec2& A, vec2& B);
	void rotate(double theta);
	void setDirection(vec2& v);
	void setCenter(vec2& center);
	vec2 getAxis();
	vec2 getCenter();
//private:
	vec2 m_center, m_c1, m_c2, m_c3, m_c4, m_v1, m_v2, m_v3, m_v4;
	float m_hw, m_hl;
};

bool collide(vec2& a, vec2& b);
bool collision(BoundingBox& a, BoundingBox& b);
#endif