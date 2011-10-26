#include "OpenGLController.h"

#include "SphereObject.h"
#include "DebugObject.h"

OpenGLController::OpenGLController () {
	m_rootObject = new Object(NULL);
	ResetCamera();
}

OpenGLController::~OpenGLController () {
	delete m_rootObject;
}

void OpenGLController::ResetCamera () {
	m_position = vec4(-45.8f, 16.3f, 0.0f, 1.0f);
	m_viewAngle = 0.0f;
	m_yawAngle = -0.4f;
    m_aspectRatio = 1.33f;
}

void OpenGLController::InitScene () {
// sun
	// large, red
	Object* sun = new SphereObject(m_rootObject, 4, e_NormalTypeSmooth);
	sun->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	sun->SetAngularVelocity(vec3(0.0f, 50.0f, 0.0f));
	sun->SetScale(3.0f);
	sun->SetAmbientColor(vec3(1.0f, 0.1f, 0.0f));
	sun->SetAmbientCoefficient(1.0f);
	sun->SetDiffuseColor(vec3(0.0f, 0.0f, 0.0f));
	sun->SetDiffuseCoefficient(0.0f);
	sun->SetSpecularColor(vec3(0.0f, 0.0f, 0.0f));
	sun->SetSpecularCoefficient(0.0f);
	sun->SetSpeculatExponent(1.0f);

	// Base for all the planets
	Object* iceBase = new Object(m_rootObject);
	iceBase->SetAngularVelocity(vec3(0.0f, 40.0f, 0.0f));

	Object* swampBase = new Object(m_rootObject);
	swampBase->SetAngularVelocity(vec3(0.0f, 70.0f, 0.0f));
	
	Object* waterBase = new Object(m_rootObject);
	waterBase->SetAngularVelocity(vec3(0.0f, 40.0f, 0.0f));
	
	Object* rustyBase = new Object(m_rootObject);
	rustyBase->SetAngularVelocity(vec3(0.0f, 50.0f, 0.0f));

	// ice 
	// small, med-low complex, blue, flat shade, specular
	Object* iceProxy = new Object(iceBase);
	iceProxy->SetPosition(vec3(-7.0f, 0.0f, 0.0f));
	iceProxy->SetAngularVelocity(vec3(0.0f, 100.0f, 0.0f));

	Object* icePlanet = new SphereObject(iceProxy, 2, e_NormalTypeFlat);
	icePlanet->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	icePlanet->SetAngularVelocity(vec3(0.0f, -150.0f, 0.0f));
	icePlanet->SetScale(0.7f);
	icePlanet->SetVertexLighting(true);
	icePlanet->SetAmbientColor(vec3(0.3f, 0.8f, 1.0f));
	icePlanet->SetAmbientCoefficient(0.8f);
	icePlanet->SetDiffuseColor(vec3(0.5f, 0.0f, 1.0f));
	icePlanet->SetDiffuseCoefficient(1.0f);
	icePlanet->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	icePlanet->SetSpecularCoefficient(0.5f);
	icePlanet->SetSpeculatExponent(0.5f);

	Object* iceMoon = new SphereObject(iceProxy, 3, e_NormalTypeSmooth);
	iceMoon->SetPosition(vec3(-1.0f, 0.0f, 0.0f));
	iceMoon->SetAngularVelocity(vec3(0.0f, 0.0f, 0.0f));
	iceMoon->SetScale(0.3f);
	iceMoon->SetAmbientColor(vec3(0.4f, 0.4f, 0.4f));
	iceMoon->SetAmbientCoefficient(1.0f);
	iceMoon->SetDiffuseColor(vec3(1.0f, 0.0f, 0.0f));
	iceMoon->SetDiffuseCoefficient(0.3f);
	iceMoon->SetSpecularColor(vec3(0.0f, 0.0f, 1.0f));
	iceMoon->SetSpecularCoefficient(0.0f);
	iceMoon->SetSpeculatExponent(0.1f);

	// swamp
	// medium, med complex, green-brown, gourard shade, specular
	Object* swamp = new SphereObject(swampBase, 2, e_NormalTypeSmooth);
	swamp->SetPosition(vec3(12.0f, 0.0f, 0.0f));
	swamp->SetScale(1.1f);
	swamp->SetAmbientColor(vec3(0.0f, 1.0f, 0.0f));
	swamp->SetAmbientCoefficient(0.5f);
	swamp->SetDiffuseColor(vec3(0.0f, 0.0f, 1.0f));
	swamp->SetDiffuseCoefficient(0.0f);
	swamp->SetSpecularColor(vec3(0.0f, -1.0f, 1.0f));
	swamp->SetSpecularCoefficient(0.2f);
	swamp->SetSpeculatExponent(1.0f);

	// water
	// medium, high complex, phong shade, specular
	SphereObject* water = new SphereObject(waterBase, 4, e_NormalTypeSmooth);
	water->SetPosition(vec3(18.0f, 0.0f, 0.0f));
	water->SetScale(1.2f);
	water->SetAmbientColor(vec3(0.0f, 0.0f, 1.0f));
	water->SetAmbientCoefficient(0.8f);
	water->SetDiffuseColor(vec3(0.0f, 0.0f, 1.0f));
	water->SetDiffuseCoefficient(0.0f);
	water->SetSpecularColor(vec3(1.0f, 1.0f, 1.0f));
	water->SetSpecularCoefficient(0.1f);
	water->SetSpeculatExponent(10.0f);

	// rusty
	// medium, med-high comple, brown-orange, no specular
	SphereObject* rusty = new SphereObject(rustyBase, 3, e_NormalTypeSmooth);
	rusty->SetPosition(vec3(23.0f, 0.0f, 0.0f));
	rusty->SetScale(0.8f);
	rusty->SetAmbientColor(vec3(1.0f, 0.4f, 0.1f));
	rusty->SetAmbientCoefficient(1.0f);
	rusty->SetDiffuseColor(vec3(0.0f, 0.4f, 0.1f));
	rusty->SetDiffuseCoefficient(-1.0f);
	rusty->SetSpecularColor(vec3(0.0f, 0.0f, 1.0f));
	rusty->SetSpecularCoefficient(0.0f);
	rusty->SetSpeculatExponent(1.0f);
}

void OpenGLController::Init () {
	InitScene();

	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
	glGenBuffers( 1, &ShaderState::s_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, ShaderState::s_buffer );

	int dataSize = m_rootObject->GetTreeDataSize();
	glBufferData(GL_ARRAY_BUFFER, dataSize, NULL, GL_STATIC_DRAW);

	ShaderState::InitShaders();

	m_rootObject->LoadTreeData(0);

	glEnable(GL_DEPTH_TEST);
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

void OpenGLController::Update () {
	float delta = m_timer.GetElapsedTime();
	m_timer.Reset();

	m_rootObject->UpdateTree(delta);
}

void OpenGLController::Render () {
	vec4 target = m_position + Angel::RotateY(-1.0f * m_viewAngle * 180.0f / 3.14159f) * Angel::RotateZ(m_yawAngle * 180.0f / 3.14159f) * vec4(1.0f, 0.0f, 0.0f, 0.0f);
	mat4 lookat = Angel::LookAt(m_position, target, vec4(0.0f, 1.0f, 0.0f, 0.0f));
	mat4 projectionMatrix = Angel::Perspective(45.0f, m_aspectRatio, 0.5f, 40.0f);

	ShaderState::m_viewportMatrix = projectionMatrix * lookat;
	ShaderState::m_eyePosition = vec3(m_position.x, m_position.y, m_position.z);

	m_rootObject->RenderTree();	
}

void OpenGLController::MoveForward (float dist) {
	m_position += dist * Angel::RotateY(-1.0f * m_viewAngle * 180.0f / 3.14159f) * Angel::RotateZ(m_yawAngle * 180.0f / 3.14159f) * vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

void OpenGLController::MoveSideways (float dist) {
	m_position += dist * Angel::RotateY(-1.0f * m_viewAngle * 180.0f / 3.14159f) * Angel::RotateZ(m_yawAngle * 180.0f / 3.14159f) * vec4(0.0f, 0.0f, 1.0f, 0.0f);
}

void OpenGLController::ChangeAspectRatio (float dist) { 
	m_aspectRatio += dist; 

	if (m_aspectRatio < 0.1f)
		m_aspectRatio = 0.1f;
}