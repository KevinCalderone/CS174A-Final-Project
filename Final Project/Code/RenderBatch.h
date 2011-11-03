#ifndef __RENDERBATCH_H__
#define __RENDERBATCH_H__

#include <string>

#include "EffectState.h"

struct RenderBatch
{
	std::string m_geometryID;
	EffectState m_effectState;
};

#endif