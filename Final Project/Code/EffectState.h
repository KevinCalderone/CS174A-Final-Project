#ifndef __EFFECTSTATE_H__
#define __EFFECTSTATE_H__

#include <string>

#include "mat.h"

struct EffectState
{
	mat4 m_modelView;
	mat4 m_projection;

	std::string m_texture0;
};

#endif