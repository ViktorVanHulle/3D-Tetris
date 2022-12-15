#ifndef TUNNEL_H_
#define TUNNEL_H_

#include "Externs.h"
#include "Shaders.h"
#include "Window.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Tunnel {
private:
	Window window;
	GLuint tunnel_program;
	std::shared_ptr<Shader> shader;
	float texture_ratio = 0.0f;
	unsigned int tunnel_VAO;
	unsigned int farVAO;
	unsigned int sideVAO;
	unsigned int EBO_white;
	unsigned int EBO_black;
	unsigned int EBO_whiteFar;
	unsigned int EBO_blackFar;
public:
	Tunnel();
	void createTunnel();
	void createFarWall();
	void createSideWall();
	void drawTunnel();
	void drawFarWall();
	void drawSideWall_L();
	void drawSideWall_R();
	void drawSideWall_T();
	void drawSideWall_B();
	unsigned int getVAO() { return tunnel_VAO; };
	unsigned int getEBOWhite() { return EBO_black; };
	unsigned int getEBOBlack() { return EBO_white; };
	GLuint getTunnelProgram() { return tunnel_program; };
	void setTextureRatio(float ratio) { this->texture_ratio = ratio; };
};

#endif // !TUNNEL_H_

