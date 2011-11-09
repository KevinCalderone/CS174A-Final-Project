#ifndef __GROUND_H__
#define __GROUND_H__

#include "RenderBatch.h"

class Ground
{

public:
	Ground();
	~Ground();

	void setRenderBatch(RenderBatch* rb);
	RenderBatch* getRenderBatch ();

protected:
	RenderBatch* m_render;

};


#endif