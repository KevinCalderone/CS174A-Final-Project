// ------------------------
// GLUT harness v. 1.0
// ------------------------

#include <stdlib.h>
#include "Timer.h"
#include "GameManager.h"
#include "GraphicsManager.h"

// This is just for testing until you get this incorportated into GameManager
GraphicsManager* graphicsManager;
static GameManager* gameManager;

const int FPS = 60;

void initGlut (int& argc, char** argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(640, 480);
	glutCreateWindow("CS174A Final Project");
}

// Called when the window needs to be redrawn.
void callbackDisplay () {
	// This is just for testing until you get this incorportated into GameManager
	graphicsManager->ClearScreen();
	
	{
		static float theta = 0.0f;
		theta += 1.0f;

		RenderBatch batch;
		
		// it currently ignores this any just uses a cube
		// This will take in names specified in the GeometryLibrary.txt file
		batch.m_geometryID = "test";	

		// This probably should be passed in once instead of per object, will probably move this to a seperate call like SetCamera()
		batch.m_effectState.m_projectionMatrix = mat4();	

		// Modelview matrix that you will calculate from the objects position, rotation, scale
		batch.m_effectState.m_modelviewMatrix = Angel::Scale(0.5f, 0.5f, 0.5f) * Angel::RotateX(theta) * Angel::RotateY(theta)* Angel::RotateZ(theta);
		
		// Use a name that is specified in the TextureLibrary.txt file, or else it will will just draw black
		batch.m_effectState.m_texture0 = "panda";	

		graphicsManager->Render(batch);
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
	// starting to replace calls through GameManager
	gameManager = new GameManager();
	gameManager->initGame();
	graphicsManager = gameManager->getGraphicsManager();
	
	glutMainLoop();
	return 0;
}
