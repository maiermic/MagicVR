#include <magicvr/ExitGlut.hpp>
#include "magicvr/GlutFramework.hpp"

namespace glutFramework {
	GlutFramework *GlutFramework::instance = nullptr;
	
	GlutFramework::GlutFramework() : _title("GLUT Framework") {
	}

    void GlutFramework::title(const std::string &_title) {
        GlutFramework::_title = _title;
    }

	void GlutFramework::startFramework(int argc, char *argv[]) {
		setInstance();	// Sets the instance to self, used in the callback wrapper functions
		
		// Initialize GLUT
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		createWindow();

		// Function callbacks with wrapper functions
		glutReshapeFunc(reshapeWrapper);
		glutMouseFunc(mouseButtonPressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		glutDisplayFunc(displayWrapper);
		glutKeyboardFunc(keyboardDownWrapper);
		glutKeyboardUpFunc(keyboardUpWrapper);
		glutSpecialFunc(specialKeyboardDownWrapper);
		glutSpecialUpFunc(specialKeyboardUpWrapper);
		glutIdleFunc(idleWrapper);
		glutMainLoop();
	}

	int GlutFramework::createWindow() {
		return glutCreateWindow(_title.c_str());
	}

	void GlutFramework::specialKeyboardUp(int key, int x, int y) {
		// may be overwritten by sub-class
	}

	void GlutFramework::specialKeyboardDown(int key, int x, int y) {
		// may be overwritten by sub-class
	}

	void GlutFramework::keyboardDown( unsigned char key, int x, int y )
	{
		if (key==27) { // 27 represents the ESC key
			throw ExitGlut();
		}
	}

	void GlutFramework::keyboardUp(unsigned char key, int x, int y) {
		// may be overwritten by sub-class
	}

	void GlutFramework::mouseMove(int x, int y) {
		// may be overwritten by sub-class
	}

	void GlutFramework::mouseButtonPress(int button, int state, int x, int y) {
		// may be overwritten by sub-class
	}

	void GlutFramework::setInstance() {
		instance = this;
	}
	
	void GlutFramework::idle() {
		glutPostRedisplay();
	}

	void GlutFramework::displayFramework() {
		static OSG::Time prevT = OSG::getSystemTime();
		OSG::Time currT = OSG::getSystemTime();
		OSG::Time deltaT = currT - prevT;

		display(deltaT);

		prevT = currT;
	}
	
	// ******************************************************************
	// ** Static functions which are passed to Glut function callbacks **
	// ******************************************************************
	
	void GlutFramework::displayWrapper() {
		instance->displayFramework(); 
	}
	
	void GlutFramework::reshapeWrapper(int width, int height) {
		instance->reshape(width, height);
	}
	
	void GlutFramework::idleWrapper() {
		instance->idle();
	}
	
	void GlutFramework::mouseButtonPressWrapper(int button, int state, int x, int y) {
		instance->mouseButtonPress(button, state, x, y);
	}
	
	void GlutFramework::mouseMoveWrapper(int x, int y) {
		instance->mouseMove(x, y);
	}
										 
	void GlutFramework::keyboardDownWrapper(unsigned char key, int x, int y) {
		instance->keyboardDown(key,x,y);
	}
	
	void GlutFramework::keyboardUpWrapper(unsigned char key, int x, int y) {
		instance->keyboardUp(key,x,y);
	}
	
	void GlutFramework::specialKeyboardDownWrapper(int key, int x, int y) {
		instance->specialKeyboardDown(key,x,y);
	}
	
	void GlutFramework::specialKeyboardUpWrapper(int key, int x, int y) {
		instance->specialKeyboardUp(key,x,y);
	}
	
} // namespace
