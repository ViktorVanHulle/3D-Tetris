#ifndef GAME_H_
#define GAME_H_

#include "Externs.h"
#include "Window.h"
#include "GameRenderer.h"
#include "TextureLoader.h"

class Game {
private:
	bool pressed = false;
	bool textureMode = false;
	bool lightingMode = false;
	float passTime = 0.0f;
	float lastFrame = glfwGetTime();
public:
	Game() { this->window = Window::getInstance(); };
	Window window;
	GameRenderer* gameRenderer;
	TextureLoader* textureLoader;
	
	glm::mat4 perspectiveCamera;
	glm::mat4 viewMatrix;
	void init();
	void run();
	void inputChecker();
	void timer();
	void gameOver();
};

#endif // !GAME_H_
