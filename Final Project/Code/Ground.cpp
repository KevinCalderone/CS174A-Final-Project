#include "Ground.h"

Ground::Ground() 
	: m_render(NULL)
{
}

Ground::~Ground() {
	if (m_render != NULL)
		delete m_render;
}

void Ground::setRenderBatch(RenderBatch* rb) {
	m_render = rb;
}

RenderBatch* Ground::getRenderBatch () {
	return m_render;
}