#include "SphereObject.h"

SphereObject::SphereObject (Object* parent, unsigned int numTimesToSubdivide, NormalType normalType) 
	: Object(parent), m_verticiesInitialized(0), m_normalType(normalType)
{
	InitializeData(numTimesToSubdivide);

	m_state.m_ambientColor = vec3(1.0f, 1.0f, 1.0f);
}

SphereObject::~SphereObject () {

}

void SphereObject::Triangle (const point4& a, const point4& b, const point4& c) {
	vec3 flatNormal = normalize( cross(b - a, c - b) );

	m_data[m_verticiesInitialized].position.x = a.x;
	m_data[m_verticiesInitialized].position.y = a.y;
	m_data[m_verticiesInitialized].position.z = a.z;
	switch (m_normalType) {
		case e_NormalTypeFlat:
			m_data[m_verticiesInitialized].normal = flatNormal;
			break;
		case e_NormalTypeSmooth:
			m_data[m_verticiesInitialized].normal = normalize(vec3(a.x, a.y, a.z));
			break;
	};
	m_verticiesInitialized++;

	m_data[m_verticiesInitialized].position.x = b.x;
	m_data[m_verticiesInitialized].position.y = b.y;
	m_data[m_verticiesInitialized].position.z = b.z;
	switch (m_normalType) {
		case e_NormalTypeFlat:
			m_data[m_verticiesInitialized].normal = flatNormal;
			break;
		case e_NormalTypeSmooth:
			m_data[m_verticiesInitialized].normal = normalize(vec3(b.x, b.y, b.z));
			break;
	};
	m_verticiesInitialized++;

	m_data[m_verticiesInitialized].position.x = c.x;
	m_data[m_verticiesInitialized].position.y = c.y;
	m_data[m_verticiesInitialized].position.z = c.z;
	switch (m_normalType) {
		case e_NormalTypeFlat:
			m_data[m_verticiesInitialized].normal = flatNormal;
			break;
		case e_NormalTypeSmooth:
			m_data[m_verticiesInitialized].normal = normalize(vec3(c.x, c.y, c.z));
			break;
	};
	m_verticiesInitialized++;
}

point4 SphereObject::Unit (const point4& p) {
    float len = p.x*p.x + p.y*p.y + p.z*p.z;
    
    point4 t;
    if ( len > DivideByZeroTolerance ) {
	t = p / sqrt(len);
	t.w = 1.0;
    }

    return t;
}

void SphereObject::DivideTriangle ( const point4& a, const point4& b, const point4& c, int count ) {
    if ( count > 0 ) {
        point4 v1 = Unit( a + b );
        point4 v2 = Unit( a + c );
        point4 v3 = Unit( b + c );
        DivideTriangle(  a, v1, v2, count - 1 );
        DivideTriangle(  c, v2, v3, count - 1 );
        DivideTriangle(  b, v3, v1, count - 1 );
        DivideTriangle( v1, v3, v2, count - 1 );
    }
    else {
        Triangle( a, b, c );
    }
}

static unsigned int pow (unsigned int num, unsigned int power) {
	if (power == 0)
		return 1;
	else
		return num * pow(num, power - 1);
}

void SphereObject::InitializeData (unsigned int count)
{
	AllocateVertexData(3 * pow(4, count + 1));

    point4 v[4] = {
		vec4( 0.0, 0.0, 1.0, 1.0 ),
		vec4( 0.0, 0.942809, -0.333333, 1.0 ),
		vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
		vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };

    DivideTriangle( v[0], v[1], v[2], count );
    DivideTriangle( v[3], v[2], v[1], count );
    DivideTriangle( v[0], v[3], v[1], count );
    DivideTriangle( v[0], v[2], v[3], count );
}