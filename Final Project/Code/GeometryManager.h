#ifndef __GEOMETRYMANAGER_H__
#define __GEOMETRYMANAGER_H__

#include <map>

class GeometryManager
{
public:
	GeometryManager ();
	~GeometryManager ();

private:
	std::map<std::string, int> m_geometry;
};

#endif