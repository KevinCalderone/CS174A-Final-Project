#include "BoundingBox.h"

BoundingBox::BoundingBox(vec2& center, float hw, float hl)
{
	m_hw = hw;
	m_hl = hl;
	m_center = center;
	m_v1 = vec2(-hw,hl);
	m_v2 = vec2(hw,hl);
	m_v3 = vec2(-hw,-hl);
	m_v4 = vec2(hw,-hl);
	m_c1 = center+m_v1;
	m_c2 = center+m_v2;
	m_c3 = center+m_v3;
	m_c4 = center+m_v4;

	RenderBatch* batch = new RenderBatch();
	batch->m_geometryID = "boundingbox";	
	batch->m_effectParameters.m_modelviewMatrix =  mat4();
	batch->m_effectParameters.m_materialAmbient = vec3(1.0f, 0.0f, 0.0f) * 2.0f;
	batch->m_effectParameters.m_materialDiffuse = vec3(1.0f, 0.0f, 0.0f) * 1.0f;
	batch->m_effectParameters.m_materialSpecular = vec3(1.0f, 0.0f, 0.0f) * 0.2f;
	batch->m_effectParameters.m_materialSpecularExponent = 6.0f;
	batch->m_effectParameters.m_materialGloss = 0.0f;
	batch->m_effectParameters.m_diffuseTexture = "none";	
	batch->m_effectParameters.m_normalMap = "none";
	this->setRenderBatch(batch);
}

void BoundingBox::setRenderBatch(RenderBatch* rb) {
	m_render = rb;
}

RenderBatch* BoundingBox::getRenderBatch () {
	return m_render;
}

void BoundingBox::update(GLfloat x, GLfloat z, float size)
{
	if(m_render!=NULL)
		m_render->m_effectParameters.m_modelviewMatrix = Angel::Translate(vec3(m_center.x,0,m_center.y))
														* Angel::Scale(vec3(size))
														* Angel::RotateY((GLfloat)90+atan2(x,z)/DegreesToRadians);
}

BoundingBox::~BoundingBox(){}

vec2 BoundingBox::calc(vec2& A, vec2& B)
{
	float min = 10000;
	float max = 0;
	double r;
	vec2 p;

	r = (A.y-m_c1.y)*(A.y-B.y)-(A.x-m_c1.x)*(B.x-A.x);
	r = r / (length(A-B)*length(A-B));
	p = vec2(A.x+r*(B.x-A.x), A.y+r*(B.y-A.y));
	if(length(A-p) > max)
		max = length(A-p);
	if(length(A-p) < min)
		min = length(A-p);

	r = (A.y-m_c2.y)*(A.y-B.y)-(A.x-m_c2.x)*(B.x-A.x);
	r = r / (length(A-B)*length(A-B));
	p = vec2(A.x+r*(B.x-A.x), A.y+r*(B.y-A.y));
	if(length(A-p) > max)
		max = length(A-p);
	if(length(A-p) < min)
		min = length(A-p);

	r = (A.y-m_c3.y)*(A.y-B.y)-(A.x-m_c3.x)*(B.x-A.x);
	r = r / (length(A-B)*length(A-B));
	p = vec2(A.x+r*(B.x-A.x), A.y+r*(B.y-A.y));
	if(length(A-p) > max)
		max = length(A-p);
	if(length(A-p) < min)
		min = length(A-p);

	r = (A.y-m_c4.y)*(A.y-B.y)-(A.x-m_c4.x)*(B.x-A.x);
	r = r / (length(A-B)*length(A-B));
	p = vec2(A.x+r*(B.x-A.x), A.y+r*(B.y-A.y));
	if(length(A-p) > max)
		max = length(A-p);
	if(length(A-p) < min)
		min = length(A-p);


	return vec2(min, max);
}

void BoundingBox::rotate(double theta)
{
	if(theta > 360) theta -= 360;
	if(theta < -360) theta += 360;
	theta *= DegreesToRadians;
	m_v1 = vec2(m_v1.x*cos(theta)-m_v1.y*sin(theta), m_v1.x*sin(theta)+m_v1.y*cos(theta));
	m_v2 = vec2(m_v2.x*cos(theta)-m_v2.y*sin(theta), m_v2.x*sin(theta)+m_v2.y*cos(theta));
	m_v3 = vec2(m_v3.x*cos(theta)-m_v3.y*sin(theta), m_v3.x*sin(theta)+m_v3.y*cos(theta));
	m_v4 = vec2(m_v4.x*cos(theta)-m_v4.y*sin(theta), m_v4.x*sin(theta)+m_v4.y*cos(theta));
	m_c1 = m_center+m_v1;
	m_c2 = m_center+m_v2;
	m_c3 = m_center+m_v3;
	m_c4 = m_center+m_v4;
}

vec2 BoundingBox::getAxis()
{
	return normalize(m_c1-m_c2);
}

void BoundingBox::setCenter(vec2& center)
{
	m_center = center;
	rotate(0.f);
}

vec2 BoundingBox::getCenter()
{
	return m_center;
}

void BoundingBox::setDirection(vec2& w)
{
	vec2 v = normalize(w);
	vec2 u = normal(v);
	m_v1 = (-m_hw*u) + (m_hl*v);
	m_v2 = (m_hw*u) + (m_hl*v);
	m_v3 = (-m_hw*u) + (-m_hl*v);
	m_v4 = (m_hw*u) + (-m_hl*v);
	m_c1 = m_center+m_v1;
	m_c2 = m_center+m_v2;
	m_c3 = m_center+m_v3;
	m_c4 = m_center+m_v4;
}

bool collide(vec2& a, vec2& b)
{
	return (a.y > b.x && b.y > a.x);
}

bool collision(BoundingBox& a, BoundingBox& b)
{
	vec2 Axis = a.getAxis();
	vec2 mid = (a.getCenter() + b.getCenter()) / 2.0;
	vec2 A = mid - (1000*Axis);
	vec2 B = mid + (1000*Axis);
	Axis = normal(Axis);
	vec2 C = mid - (1000*Axis);
	vec2 D = mid + (1000*Axis);
	Axis = b.getAxis();
	vec2 E = mid - (1000*Axis);
	vec2 F = mid + (1000*Axis);
	Axis = normal(Axis);
	vec2 G = mid - (1000*Axis);
	vec2 H = mid + (1000*Axis);

	return (collide(a.calc(A,B),b.calc(A,B)) &&
		collide(a.calc(C,D),b.calc(C,D)) &&
		collide(a.calc(E,F),b.calc(E,F)) &&
		collide(a.calc(G,H),b.calc(G,H)));
}