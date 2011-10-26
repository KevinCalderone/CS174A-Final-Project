#include "Object.h"

typedef Angel::vec4 point4;

enum NormalType { e_NormalTypeFlat, e_NormalTypeSmooth };

class SphereObject : public Object
{
public:
	SphereObject (Object* parent, unsigned int numTimesToSubdivide, NormalType normalType);
	~SphereObject ();

private:
	point4 Unit (const point4& p);
	void Triangle (const point4& a, const point4& b, const point4& c);
	void DivideTriangle( const point4& a, const point4& b, const point4& c, int count );
	void InitializeData (unsigned int count);

	const NormalType m_normalType;
	unsigned int m_verticiesInitialized;
};
