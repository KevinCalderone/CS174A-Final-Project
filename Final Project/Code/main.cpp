// ------------------------
// GLUT harness v. 1.0
// ------------------------

#include <stdlib.h>
#include "Timer.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "GraphicsSettings.h"

// This is just for testing until you get this incorportated into GameManager
GraphicsManager* graphicsManager;
static GameManager* gameManager;

const int FPS = 60;

void initGlut (int& argc, char** argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(c_window_width, c_window_height);
	glutCreateWindow("CS17A Final Project");
}

static void SetCameraOrthogonal () {
	RenderParameters& renderParameters = graphicsManager->GetRenderParameters();
	renderParameters.m_projectionMatrix = mat4();
}

static void SetupCamera (vec4 playerPos) {
	vec4 playerPosition = playerPos;
	vec4 eyePosition = playerPosition + vec4(0.0f, 15.0f, 15.0f, 0.0f);
	RenderParameters& renderParameters = graphicsManager->GetRenderParameters();

	renderParameters.m_eyePosition = vec3(eyePosition.x, eyePosition.y, eyePosition.z);
	renderParameters.m_projectionMatrix = 
		Angel::Perspective(45.0f, 4.0f/3.0f, 0.5f, 50.0f) * 
		Angel::LookAt(eyePosition, playerPosition, vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

// Called when the window needs to be redrawn.
void callbackDisplay () {
	// This is just for testing until you get this incorportated into GameManager
	graphicsManager->ClearScreen();
	
	{
		static float theta = 0.0f;
		theta += 1.0f;

		SetupCamera(*gameManager->getPlayer()->getPosition());

		RenderParameters& renderParameters = graphicsManager->GetRenderParameters();

		// Position lights at player postion
		renderParameters.m_pointLightPosition[0] = *gameManager->getPlayer()->getPosition() + vec3(0.0f, 1.5f, -1.5f);
		renderParameters.m_pointLightPosition[1] = *gameManager->getPlayer()->getPosition() + vec3(0.0f, 0.5f, -2.5f);
		
		// Muzzle flash
		float flashIntensity = cos((3.14159 / 2.0f) * (fmod(theta, 20.0f) < 13.0f ? fmod(theta, 20.0f) / 13.0f : 1.0f));
		renderParameters.m_pointLightDiffuse[1] = vec3(3.0f, 3.0f, 0.0f) * flashIntensity;
		renderParameters.m_pointLightSpecular[1] = vec3(2.0f, 2.0f, 0.0f) * flashIntensity;
		renderParameters.m_pointLightRange[1] = 8.0f * flashIntensity;
		renderParameters.m_pointLightFalloff[1] = 2.0f * flashIntensity;

		// Flickering Torch
		renderParameters.m_pointLightRange[0] = 11.0f + 2.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f ;
		renderParameters.m_pointLightFalloff[0] = 2.0f + 1.0f * (sin(theta * 0.12f) + sin(theta * 0.14f) + sin(theta * 0.09f))/3.0f;

		gameManager->Render();
	}

	// This is just for testing until you get this incorportated into GameManager
	graphicsManager->SwapBuffers();
}

// Called when the window is resized.
void callbackReshape (int width, int height) {

}

// Called when a key is pressed. x, y is the current mouse position.
void callbackKeyboard (unsigned char key, int x, int y) {
	gameManager->callbackKeyboard(key, x, y);
}

void callbackKeyUp(unsigned char key, int x, int y) {
	gameManager->callbackKeyUp(key, x, y);
}

// Called when a mouse button is pressed or released
void callbackMouse (int button, int state, int x, int y) {

}

// Called when the mouse is moved with a button pressed
void callbackMotion (int x, int y) {

}

// Called when the mouse is moved with no buttons pressed
void callbackPassiveMotion (int x, int y) {

}

// Called when the system is idle. Can be called many times per frame.
void callbackIdle () {

}

// Called when the timer expires
void callbackTimer (int) {
	glutTimerFunc(1000/FPS, callbackTimer, 0);
	glutPostRedisplay();
}

void initCallbacks () {
	glutDisplayFunc(callbackDisplay);
	glutReshapeFunc(callbackReshape);
	glutKeyboardFunc(callbackKeyboard);
	glutKeyboardUpFunc(callbackKeyUp);
	glutMouseFunc(callbackMouse);
	glutMotionFunc(callbackMotion);
	glutPassiveMotionFunc(callbackPassiveMotion);
	glutIdleFunc(callbackIdle);
	glutTimerFunc(1000/30, callbackTimer, 0);
}

int main (int argc, char** argv) {
	initGlut(argc, argv);
	initCallbacks();
	glewInit();

	gameManager = new GameManager();
	gameManager->initGame();
	graphicsManager = gameManager->getGraphicsManager();

	RenderParameters& renderParameters = graphicsManager->GetRenderParameters();
	renderParameters.m_lightDirection = vec3(1.0f, 2.0f, 2.0f);
	renderParameters.m_lightAmbient = vec3(0.5f, 0.5f, 0.7f) * 0.0f;
	renderParameters.m_lightDiffuse = vec3(1.0f, 1.0f, 0.6f) * 0.0f;
	renderParameters.m_lightSpecular = vec3(1.0f, 1.0f, 0.7f) * 0.0f;
	renderParameters.m_environmentMap = "envMap";
	
	renderParameters.m_pointLightAmbient[0] = vec3(0.1f, 0.0f, 0.0f);
	renderParameters.m_pointLightDiffuse[0] = vec3(1.5f, 0.5f, 0.0f);
	renderParameters.m_pointLightSpecular[0] = vec3(2.5f, 1.5f, 0.0f);
	renderParameters.m_pointLightRange[0] = 12.0f;
	renderParameters.m_pointLightFalloff[0] = 5.0f;
	
	renderParameters.m_pointLightPosition[1] = vec3(5.0f, 1.0f, 0.0f);
	renderParameters.m_pointLightDiffuse[1] = vec3(0.0f, 0.0f, 0.0f);
	renderParameters.m_pointLightSpecular[1] = vec3(0.0f, 0.0f, 0.0f);
	renderParameters.m_pointLightRange[1] = 10.0f;
	renderParameters.m_pointLightFalloff[1] = 2.0f;
	/*
	renderParameters.m_pointLightPosition[2] = vec3(0.0f, 1.0f, 5.0f);
	renderParameters.m_pointLightDiffuse[2] = vec3(0.0f, 1.0f, 0.0f);
	renderParameters.m_pointLightSpecular[2] = vec3(0.0f, 1.0f, 0.0f);
	renderParameters.m_pointLightRange[2] = 8.0f;
	renderParameters.m_pointLightFalloff[2] = 2.0f;
	*/
	// No color correction
	renderParameters.m_colorCorrection = mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
	);
	
	/*
	// Under water looking
	renderParameters.m_colorCorrection = mat4(
		0.5f, 0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.5f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
	);
	*/
	/*
	// Black and White
	renderParameters.m_colorCorrection = mat4(
		0.33f, 0.33f, 0.33f, 0.0f,
		0.33f, 0.33f, 0.33f, 0.0f, 
		0.33f, 0.33f, 0.33f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f
	);
	*/

	glutMainLoop();
	return 0;
}
