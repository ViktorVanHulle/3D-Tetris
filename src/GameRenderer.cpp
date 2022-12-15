#include "GameRenderer.h"

GameRenderer::GameRenderer()
{
	init();
}

void GameRenderer::init()
{
	this->window = Window::getInstance();
	tunnel = new Tunnel();
	//first active block
	activeBlock = new Block();

	glGenVertexArrays(1, &tunnelVAO);

	tunnel->createTunnel();
	activeBlock->createBlock();
}

void GameRenderer::renderer()
{

	renderTunnel();
	renderBlock();

	glBindVertexArray(0);
	glUseProgram(0);
}



void GameRenderer::renderTunnel()
{
	glBindVertexArray(tunnel->getVAO());
	tunnel->drawTunnel();

	glBindVertexArray(0);
	glUseProgram(0);
}

void GameRenderer::renderBlock()
{
	tunnel->setTextureRatio(ratio);
	for (auto& block : solid_blocks) { block.setTextureRatio(ratio); block.drawSolidBlock(); }

	if (activeBlock->getActive()) {
		glBindVertexArray(activeBlock->getVAO());
		activeBlock->setTextureRatio(ratio);
		activeBlock->drawActiveBlock();
		if (activeBlock->getZ() == 10.0f) {
			activeBlock->setActive(false);
		}
	}
	else {
		solid_blocks.push_back(*activeBlock);
		activeBlock = new Block();
		activeBlock->createBlock();
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void GameRenderer::checkBoxCollision(int key) {

	if (key == GLFW_KEY_SPACE) {
		int coll_z = 11;

		for (auto& block : solid_blocks) {

			if (activeBlock->getX() == block.getX() &&
				activeBlock->getY() == block.getY() &&
				activeBlock->getActive()) {
				if (block.getZ() < coll_z) coll_z = block.getZ();
			}
		}
		activeBlock->setZ(coll_z != 11 ? coll_z - 1 : 10);
		activeBlock->setActive(false);
	}
	else if (key == GLFW_KEY_X) { 

		activeBlock->moveTile(GLFW_KEY_X);
		for (auto& block : solid_blocks) {

			if (activeBlock->getX() == block.getX() &&
				activeBlock->getY() == block.getY() &&
				activeBlock->getZ() + 1 == block.getZ() &&
				activeBlock->getActive()) {
				activeBlock->setActive(false);
			}
		}
	}
	else if (key == GLFW_KEY_UP) {
		bool taken = false;
		for (auto& block : solid_blocks) {

			if (activeBlock->getX() == block.getX() &&
				activeBlock->getY() - 1 == block.getY() &&
				activeBlock->getZ() == block.getZ() &&
				activeBlock->getActive()) {
				taken = true;
			}
		}

		if(!taken) activeBlock->moveTile(GLFW_KEY_UP);
	}
	else if (key == GLFW_KEY_DOWN) {
		bool taken = false;
		for (auto& block : solid_blocks) {

			if (activeBlock->getX() == block.getX() &&
				activeBlock->getY() + 1 == block.getY() &&
				activeBlock->getZ() == block.getZ() &&
				activeBlock->getActive()) {
				taken = true;
			}
		}

		if (!taken) activeBlock->moveTile(GLFW_KEY_DOWN);
	}
	else if (key == GLFW_KEY_LEFT) {
		bool taken = false;
		for (auto& block : solid_blocks) {

			if (activeBlock->getX() + 1 == block.getX() &&
				activeBlock->getY() == block.getY() &&
				activeBlock->getZ() == block.getZ() &&
				activeBlock->getActive()) {
				taken = true;
			}
		}

		if (!taken) activeBlock->moveTile(GLFW_KEY_LEFT);
	}
	else if (key == GLFW_KEY_RIGHT) {
		bool taken = false;
		for (auto& block : solid_blocks) {

			if (activeBlock->getX() - 1 == block.getX() &&
				activeBlock->getY() == block.getY() &&
				activeBlock->getZ() == block.getZ() &&
				activeBlock->getActive()) {
				taken = true;
			}
		}

		if (!taken) activeBlock->moveTile(GLFW_KEY_RIGHT);
	}
}

void GameRenderer::toggleTexture(bool mode) {
	ratio = mode ? 0.0f : 0.7f;
}

bool GameRenderer::isGameOver() {

	bool isGameOver = false;

	for (auto& block : solid_blocks) {

		if (block.getZ() == 1){
			isGameOver = true;
		}
	}

	return isGameOver;
	
}