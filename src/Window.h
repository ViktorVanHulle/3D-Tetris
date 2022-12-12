#ifndef WINDOW_H_
#define WINDOW_H_

#include "Externs.h"

class Window {
private:
public:
	float SCREEN_WIDTH = 800.0f, SCREEN_HEIGHT = 800.0f;
	GLFWwindow* winWindow;
	unsigned int windowCreator();
};

#endif // !WINDOW_H_

