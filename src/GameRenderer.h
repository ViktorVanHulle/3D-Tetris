#ifndef GAME_RENDERER_H_
#define GAME_RENDERER_H_

#include "Externs.h"
#include "Tunnel.h"
#include "Window.h"
#include "Block.h"
#include <vector>

class GameRenderer {
private:
	unsigned int tunnelVAO;
	float ratio = 0.0f;
	bool illuminationMode = false;
	Tunnel* tunnel;
	Block* activeBlock;
	std::vector<Block> solid_blocks;
	Window window;
	void renderTunnel();
	void renderBlock();
public:
	GameRenderer();
	void renderer();
	void init();
	void checkBoxCollision(int key);
	void toggleTexture(bool mode) { this->ratio = mode ? 0.0f : 0.7f; };
	void toggleLighting(bool mode) { this->illuminationMode = mode; };
	bool isGameOver();
	Tunnel* getTunnel() { return tunnel; };
	Block* getActiveBlock() { return activeBlock; }
};

#endif // !GAME_RENDERER_H_

