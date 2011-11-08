// ------------------------
// GLUT harness v. 1.0
// ------------------------

#include <stdlib.h>
#include "Timer.h"
#include "GameManager.h"
#include "GraphicsManager.h"

// This is just for testing until you get this incorportated into GameManager
GraphicsManager* graphicsManager;

const int FPS = 60;

void initGlut (int& argc, char** argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(640, 480);
	glutCreateWindow("CS17A Final Project");
}

void SetupCamera (vec4 playerPos) {
	vec4 playerPosition = playerPos;
	vec4 eyePosition = playerPosition + vec4(0.0f, 2.0f, 2.0f, 1.0f);
	RenderParameters& renderParameters = graphicsManager->GetRenderParameters();

	renderParameters.m_eyePosition = vec3(eyePosition.x, eyePosition.y, eyePosition.z);
	renderParameters.m_projectionMatrix = 
		Angel::Perspective(45.0f, 4.0f/3.0f, 0.5f, 50.0f) * 
		Angel::LookAt(playerPosition + vec4(0.0f, 10.0f, 10.0f, 1.0f), playerPosition, vec4(0.0f, 1.0f, 0.0f, 0.0f));
}

// Called when the window needs to be redrawn.
void callbackDisplay () {
	// This is just for testing until you get this incorportated into GameManager
	graphicsManager->ClearScreen();
	
	{
		static float theta = 0.0f;
		theta += 1.0f;

		SetupCamera(vec4(sin(theta * DegreesToRadians), 0.0f, cos(theta* DegreesToRadians), 0.0f));
		
		{
			RenderBatch batch;
		
			batch.m_geometryID = "plane";	

			batch.m_effectParameters.m_modelviewMatrix = mat4();
		
			batch.m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f);
			batch.m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f);
			batch.m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.4f;
			batch.m_effectParameters.m_materialSpecularExponent = 15.0f;
			batch.m_effectParameters.m_materialGloss = 0.1f;
			
			batch.m_effectParameters.m_diffuseTexture = "stone";	

			graphicsManager->Render(batch);
		}
		
		{
			RenderBatch batch;
		
			batch.m_geometryID = "monster";	

			batch.m_effectParameters.m_modelviewMatrix = mat4();//Angel::RotateX(theta) * Angel::RotateY(theta)* Angel::RotateZ(theta);
		
			batch.m_effectParameters.m_materialAmbient = vec3(1.0f, 1.0f, 1.0f);
			batch.m_effectParameters.m_materialDiffuse = vec3(1.0f, 1.0f, 1.0f);
			batch.m_effectParameters.m_materialSpecular = vec3(1.0f, 1.0f, 1.0f) * 0.4f;
			batch.m_effectParameters.m_materialSpecularExponent = 20.0f;
			batch.m_effectParameters.m_materialGloss = 0.15f;

			batch.m_effectParameters.m_diffuseTexture = "monster";	

			graphicsManager->Render(batch);
		}

	}

	// This is just for testing until you get this incorportated into GameManager
	graphicsManager->SwapBuffers();
}

// Called when the window is resized.
void callbackReshape (int width, int height) {

}

// Called when a key is pressed. x, y is the current mouse position.
void callbackKeyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 27:	// esc
			exit(0);
		break;
	}
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

	// This is just for testing until you get this incorportated into GameManager
	graphicsManager = new GraphicsManager("../Data/AssetLibrary.txt");
	
	RenderParameters& renderParameters = graphicsManager->GetRenderParameters();
	renderParameters.m_lightDirection = vec3(1.0f, 2.0f, 2.0f);
	renderParameters.m_lightAmbient = vec3(0.5f, 0.5f, 0.7f);
	renderParameters.m_lightDiffuse = vec3(1.0f, 1.0f, 0.6f) * 0.4f;
	renderParameters.m_lightSpecular = vec3(1.0f, 1.0f, 0.7f);
	renderParameters.m_environmentMap = "envMap";

	glutMainLoop();
	return 0;
}
