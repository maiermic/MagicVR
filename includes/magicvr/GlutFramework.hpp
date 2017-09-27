#ifndef GLUT_FRAMEWORK_H
#define GLUT_FRAMEWORK_H

#include <string.h>

// Note: Include GLUT after the standard C++ libraries to prevent linker errors

#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGGLUT.h>

namespace glutFramework {
		
	class GlutFramework {
		static GlutFramework *instance;

    protected:
		std::string _title;

	public:
		const static int WINDOW_WIDTH = 640;
		const static int WINDOW_HEIGHT = 480;
		const static int WINDOW_X_POSITION = 100;
		const static int WINDOW_Y_POSITION = 100;

	public:
		GlutFramework();

        void title(const std::string &_title);

        /**
         * Initialize framework and start the Glut main loop.
         * It must be called after the GlutFramework class is created to start
         * the application.
         */
		void startFramework(int argc, char *argv[]);
		
		// ****************************
		// ** Subclass and Implement ** 
		// ****************************
		
		/**
		 * When GLUT determines that the normal plane for the window needs to
		 * be redisplayed, this method is called with the elapsed time since
		 * its last call.
		 * @param dTime - the change in time (seconds)
		 */
		virtual void display(OSG::Time dTime)=0;
		
		/**
		 * Called when the window dimensions change.
		 * @param width - the width of the window in pixels
		 * @param height - the height of the window in pixels
		 */
		virtual void reshape(int width, int height)=0;
		
		/**
		 * Called when the mouse buttons are pressed.
		 * @param button - the mouse buttons
		 * @param state - the state of the buttons
		 * @param x - the x coordinate
		 * @param y - the y coordinate
		 */
		virtual void mouseButtonPress(int button, int state, int x, int y);
		
		/**
		 * Called when the mouse moves on the screen.
		 * @param x - the x coordinate
		 * @param y - the y coordinate
		 */
		virtual void mouseMove(int x, int y);
		
		/**
		 * The keyboard function is called when a standard key is pressed down.
		 * By default it exits the main loop on ESC by throwing ExitGlut.
		 * @param key - the key press
		 * @param x - the x coordinate of the mouse
		 * @param y - the y coordinate of the mouse
		 */
		virtual void keyboardDown( unsigned char key, int x, int y);
		
		/**
		 * The keyboard function is called when a standard key is "unpressed".
		 * @param key - the key press
		 * @param x - the x coordinate of the mouse
		 * @param y - the y coordinate of the mouse
		 */
		virtual void keyboardUp( unsigned char key, int x, int y);
		
		/**
		 * The keyboard function is called when a special key is pressed down.
		 * (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys)
		 * http://www.opengl.org/resources/libraries/glut/spec3/node54.html
		 * @param key - the key press
		 * @param x - the x coordinate of the mouse
		 * @param y - the y coordinate of the mouse
		 */
		virtual void specialKeyboardDown( int key, int x, int y);
		
		/**
		 * The keyboard function is called when a special key is "unpressed.
		 * (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys)
		 * @param key - the key press
		 * @param x - the x coordinate of the mouse
		 * @param y - the y coordinate of the mouse
		 */
		virtual void specialKeyboardUp( int key, int x, int y );
		
		/**
		 * The instance will be set when the framework is started.
		 * This step is necessary to initialize the static instance that is
		 * used for the object oriented wrapper calls
		 */
		void setInstance(); 
		
		/**
		 * Perform background processing tasks or continuous animation when
		 * window system events are not being received.
		 * If enabled, the idle callback is continuously called when events are
		 * not being received. The callback routine has no parameters.
		 * The current window and current menu will not be changed before the
		 * idle callback. Programs with multiple windows and/or menus should
		 * explicitly set the current window and/or current menu and not rely
		 * on its current setting.
		 *
		 * The amount of computation and rendering done in an idle callback
		 * should be minimized to avoid affecting the program's interactive
		 * response. In general, not more than a single frame of rendering
		 * should be done in an idle callback.
		 */
		virtual void idle();
		
		/**
		 * Calculates the change in time since its last call.
		 * Then it calls the display(OSG::Time) function with that delta time.
		 */
		void displayFramework();

        /**
         * Creates the Glut window and returns its ID.
         * @return ID of the created Glut window.
         */
        virtual int createWindow();

		// ** Static functions which are passed to GLUT function callbacks **
		// http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.1
		static void displayWrapper();
		static void reshapeWrapper(int width, int height);
		static void idleWrapper();
		static void mouseButtonPressWrapper(int button, int state, int x, int y);
		static void mouseMoveWrapper(int x, int y);
		static void keyboardDownWrapper(unsigned char key, int x, int y);
		static void keyboardUpWrapper(unsigned char key, int x, int y);
		static void specialKeyboardDownWrapper(int key, int x, int y);
		static void specialKeyboardUpWrapper(int key, int x, int y);
	};
	
} // namespace 
#endif
