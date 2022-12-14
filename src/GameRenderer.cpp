#include "GameRenderer.h"

void GameRenderer::renderTunnel()
{
	glBindVertexArray(tunnel->getVAO());
	tunnel->drawTunnel();

	glBindVertexArray(0);
	glUseProgram(0);
}

GameRenderer::GameRenderer()
{
	init();
}

void GameRenderer::renderer()
{

	//rendering tunnel
	renderTunnel();

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameRenderer::init()
{
	tunnel = new Tunnel();
	glGenVertexArrays(1, &tunnelVAO);
	tunnel->createTunnel();

}
