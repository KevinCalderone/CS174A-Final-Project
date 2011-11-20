#ifndef __RENDERPASS_H__
#define __RENDERPASS_H__

#include <string>

enum ShaderType { e_ShaderTypeForward, e_ShaderTypePostProcess };

struct RenderPass
{
	ShaderType m_shaderType;
	GeometryType m_geometryType;

	std::string m_colorAttach0;
	std::string m_depthAttach;

	std::string m_source0;
	std::string m_source1;

	std::vector<std::string> m_flags; 
};

#endif