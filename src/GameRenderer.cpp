#include "GameRenderer.h"

void GameRenderer::renderTunnel()
{
	glBindVertexArray(tunnel->getVAO());
	tunnel->drawTunnel();

	glBindVertexArray(0);
	glUseProgram(0);
}

void GameRenderer::renderBlock()
{

	for (auto& block : solid_blocks) {
		block.drawSolidBlock();
	}

	if (activeBlock->getActive()) {
		glBindVertexArray(activeBlock->getVAO());
		activeBlock->drawActiveBlock();
	}
	else {
		solid_blocks.push_back(*activeBlock);
		activeBlock = new Block();
		activeBlock->createBlock();
	}




	glBindVertexArray(0);
	glUseProgram(0);
}

GameRenderer::GameRenderer()
{
	this->window = Window::getInstance();
	init();
}

void GameRenderer::renderer()
{

	//rendering tunnel
	renderTunnel();
	//rendering first cube
	renderBlock();

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameRenderer::init()
{
	tunnel = new Tunnel();
	//first active block
	activeBlock = new Block();

	glGenVertexArrays(1, &tunnelVAO);

	tunnel->createTunnel();
	activeBlock->createBlock();


}
