#ifndef GAME_H_
#define GAME_H_

#include "Externs.h"
#include "Window.h"
#include "GameRenderer.h"

class Game {
private:
public:
	Window* window = new Window();
	GameRenderer* gameRenderer;
	void init();
	void run();
};

#endif // !GAME_H_
