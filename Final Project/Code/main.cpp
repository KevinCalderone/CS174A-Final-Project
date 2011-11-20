// ------------------------
// GLUT harness v. 1.0
// ------------------------

#include <stdlib.h>
#include "Timer.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "GraphicsSettings.h"

// This is just for testing until you get this incorportated into GameManager
static GameManager* gameManager;

const int FPS = 60;

void initGlut (int& argc, char** argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(c_window_width, c_window_height);
	glutCreateWindow("CS17A Final Project");
}





// Called when the window needs to be redrawn.
void callbackDisplay () {
	// This is just for testing until you get this incorportated into GameManager
	gameManager->Render();
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

	glutMainLoop();
	return 0;
}
