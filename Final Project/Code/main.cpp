// ------------------------
// GLUT harness v. 1.0
// ------------------------

#include <stdlib.h>

#include "OpenGLController.h"

static OpenGLController controller;

const int FPS = 30;

void initGlut (int& argc, char** argv) { 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(640, 480);
	glutCreateWindow("CS17A Final Project");
}

// Called when the window needs to be redrawn.
void callbackDisplay () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	controller.Update();
	controller.Render();

	glutSwapBuffers();
}

// Called when the window is resized.
void callbackReshape (int width, int height) {

}

// Called when a key is pressed. x, y is the current mouse position.
void callbackKeyboard (unsigned char key, int x, int y) {
	switch (key) {
		// Translate Camera
		case 'a':
		case 'A':
			controller.MoveSideways(-1.0f);
		break;

		case 'd':
		case 'D':
			controller.MoveSideways(1.0f);
		break;

		case 'w':
		case 'W':
			controller.MoveForward(1.0f);
		break;

		case 's':
		case 'S':
			controller.MoveForward(-1.0f);
		break;

		case 'j':
		case 'J':
			controller.Turn(-0.1f);
		break;

		case 'k':
		case 'K':
			controller.Turn(0.1f);
		break;

		case 'i':
		case 'I':
			controller.TurnUp(0.1f);
		break;

		case 'm':
		case 'M':
			controller.TurnUp(-0.1f);
		break;

		// Camera Aspect Ratio (aka fovx)
		case 'o':
		case 'O':
			controller.ChangeAspectRatio(0.1f);
		break;

		case 'p':
		case 'P':
			controller.ChangeAspectRatio(-0.1f);
		break;

		case ' ':
			controller.ResetCamera();
		break;

		case 'q':
		case 'Q':
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

	controller.Init();
	glutMainLoop();
	return 0;
}
