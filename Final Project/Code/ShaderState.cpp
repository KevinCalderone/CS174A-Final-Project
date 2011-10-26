#include "ShaderState.h"

#include "Vertex.h"

// Initialize Static State
vec3 ShaderState::m_eyePosition = vec3();
vec3 ShaderState::m_lightPosition = vec3();
mat4 ShaderState::m_viewportMatrix = mat4();

GLuint ShaderState::s_program = -1;
GLuint ShaderState::s_buffer = -1;

GLuint ShaderState::a_vPosition = -1;
GLuint ShaderState::a_vNormal = -1;

GLuint ShaderState::u_eyePosition = -1;
GLuint ShaderState::u_lightPosition = -1;

GLuint ShaderState::u_viewportMatrix = -1;
GLuint ShaderState::u_modelviewMatrix = -1;

GLuint ShaderState::u_vertexLighting = -1;

GLuint ShaderState::u_ambientColor = -1;
GLuint ShaderState::u_ambientCoefficient = -1;
GLuint ShaderState::u_diffuseColor = -1;
GLuint ShaderState::u_diffuseCoefficient = -1;
GLuint ShaderState::u_specularColor = -1;
GLuint ShaderState::u_specularCoefficient = -1;
GLuint ShaderState::u_specularExponent = -1;

void ShaderState::InitShaders () {
 	// Load shaders and use the resulting shader program
	s_program = InitShader( "../Shaders/vert.txt", "../Shaders/frag.txt" );
    glUseProgram(s_program );

	// Initialize location of shader variables
	a_vPosition = glGetAttribLocation(s_program, "vPosition");
	a_vNormal = glGetAttribLocation(s_program, "vNormal");

	u_eyePosition = glGetUniformLocation(s_program, "eyePosition");
	u_lightPosition = glGetUniformLocation(s_program, "targetPosition");

	u_viewportMatrix = glGetUniformLocation(s_program, "viewportMatrix");
	u_modelviewMatrix = glGetUniformLocation(s_program, "modelviewMatrix");

	u_vertexLighting = glGetUniformLocation(s_program, "vertexLighting");

	u_ambientColor = glGetUniformLocation(s_program, "ambientColor");
	u_ambientCoefficient = glGetUniformLocation(s_program, "ambientCoefficient");
	u_diffuseColor = glGetUniformLocation(s_program, "diffuseColor");
	u_diffuseCoefficient = glGetUniformLocation(s_program, "diffuseCoefficient");
	u_specularColor = glGetUniformLocation(s_program, "specularColor");
	u_specularCoefficient = glGetUniformLocation(s_program, "specularCoefficient");
	u_specularExponent = glGetUniformLocation(s_program, "specularExponent");

    // Initialize the vertex position attribute from the vertex shader
    glEnableVertexAttribArray(a_vPosition );
    glVertexAttribPointer( a_vPosition, 3, GL_FLOAT, GL_FALSE, 24,
                           BUFFER_OFFSET(c_positionDataOffset) );

	glEnableVertexAttribArray( a_vNormal );
    glVertexAttribPointer( a_vNormal, 3, GL_FLOAT, GL_FALSE, 24,
                           BUFFER_OFFSET(c_normalDataOffset) );
}

void ShaderState::Apply () {
	glUniform3f(u_eyePosition, m_eyePosition.x,  m_eyePosition.y,  m_eyePosition.z);
	glUniform3f(u_lightPosition, m_lightPosition.x,  m_lightPosition.y,  m_lightPosition.z);

	glUniformMatrix4fv(u_viewportMatrix, 1, GL_TRUE, (GLfloat*)&m_viewportMatrix);
	glUniformMatrix4fv(u_modelviewMatrix, 1, GL_TRUE, (GLfloat*)&m_modelviewMatrix);

	glUniform1i(u_vertexLighting, m_vertexLighting);

	glUniform3f(u_ambientColor, m_ambientColor.x, m_ambientColor.y, m_ambientColor.z);
	glUniform1f(u_ambientCoefficient, m_ambientCoefficient);

	glUniform3f(u_diffuseColor, m_diffuseColor.x, m_diffuseColor.y, m_diffuseColor.z);
	glUniform1f(u_diffuseCoefficient, m_diffuseCoefficient);

	glUniform3f(u_specularColor, m_specularColor.x, m_specularColor.y, m_specularColor.z);
	glUniform1f(u_specularCoefficient, m_specularCoefficient);
	glUniform1f(u_specularExponent, m_specularExponent);
}