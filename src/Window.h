#ifndef WINDOW_H_
#define WINDOW_H_

#include "Externs.h"

class Window {
private:
public:
	float SCREEN_WIDTH = 1000.0f, SCREEN_HEIGHT = 1000.0f;
	static Window& getInstance() // Singleton is accessed via getInstance()
	{
		static Window instance; // lazy singleton, instantiated on first use
		return instance;
	}
	GLFWwindow* winWindow;
	unsigned int windowCreator();
};

#endif // !WINDOW_H_

