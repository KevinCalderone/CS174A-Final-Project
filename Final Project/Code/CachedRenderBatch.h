#ifndef __CACHEDRENDERBATCH__
#define __CACHEDRENDERBATCH__

#include "RenderBatch.h"
#include "RenderParameters.h"

struct CachedRenderBatch 
{
	CachedRenderBatch (const RenderBatch& renderBatch, const RenderParameters& renderParameters)
		: m_renderBatch(renderBatch), m_renderParameters(renderParameters) 
	{}
	
	RenderBatch m_renderBatch;
	RenderParameters m_renderParameters;
};

#endif