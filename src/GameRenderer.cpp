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
	glBindVertexArray(activeBlock->getVAO());
	activeBlock->drawBlock();

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
	activeBlock = new Block(5, 5, 1);
	glGenVertexArrays(1, &tunnelVAO);
	tunnel->createTunnel();
	activeBlock->createBlock();
	

}
