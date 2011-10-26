#include "Angel.h"

#include "Object.h"
#include "Timer.h"

const unsigned int c_num_cubes = 8;

class OpenGLController
{
public:
	OpenGLController ();
	~OpenGLController ();

	void Init ();
	void Update ();
	void Render ();

	void ResetCamera ();
	void MoveForward (float dist);
	void MoveSideways (float dist);
	void TurnUp (float angle) { m_yawAngle += angle; }
	void Turn (float angle) { m_viewAngle += angle; }

	void ChangeAspectRatio (float dist);

private:
	void InitScene ();

	// Camera state
	vec4 m_position;
	float m_viewAngle;
	float m_yawAngle;
	float m_aspectRatio;

	// Animation timer
	Timer m_timer;

	// Objects
	Object* m_rootObject;

	// OpenGL Variables
	GLuint m_program;
    GLuint m_buffer;

	// Vertex Shader
	GLint m_vPosition;
	GLint m_vColor;
	GLint m_transformMatrix;

	// Fragment Shader
	GLint m_ambientColor;
};