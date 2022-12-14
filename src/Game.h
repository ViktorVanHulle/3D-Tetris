#ifndef GAME_H_
#define GAME_H_

#include "Externs.h"
#include "Window.h"
#include "GameRenderer.h"

class Game {
private:
	bool pressed = false;
public:
	Game() { this->window = Window::getInstance(); };
	Window window;
	GameRenderer* gameRenderer;
	glm::mat4 perspectiveCamera;
	glm::mat4 viewMatrix;
	void init();
	void run();
	void inputChecker();
};

#endif // !GAME_H_
