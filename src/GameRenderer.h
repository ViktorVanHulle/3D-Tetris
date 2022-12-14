#ifndef GAME_RENDERER_H_
#define GAME_RENDERER_H_

#include "Externs.h"
#include "Tunnel.h"


class GameRenderer {
private:
	unsigned int tunnelVAO;
	Tunnel* tunnel;
	void renderTunnel();
public:

	GameRenderer();
	void renderer();
	void init();
	Tunnel* getTunnel() { return tunnel; };
};

#endif // !GAME_RENDERER_H_

