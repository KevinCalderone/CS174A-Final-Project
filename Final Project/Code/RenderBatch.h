#ifndef __RENDERBATCH_H__
#define __RENDERBATCH_H__

#include <string>

#include "EffectParameters.h"

struct RenderBatch
{
	std::string m_geometryID;
	EffectParameters m_effectParameters;
};

#endif