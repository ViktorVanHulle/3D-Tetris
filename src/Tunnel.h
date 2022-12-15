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
	bool illuminationMode = false;
	unsigned int farVAO;
	unsigned int sideVAO;
	unsigned int side2VAO;
	unsigned int EBO_white;
	unsigned int EBO_black;
	unsigned int EBO_whiteFar;
	unsigned int EBO_blackFar;
	glm::vec4 whiteColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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
	unsigned int getEBOWhite() { return EBO_black; };
	unsigned int getEBOBlack() { return EBO_white; };
	GLuint getTunnelProgram() { return tunnel_program; };
	void setTextureRatio(float ratio) { this->texture_ratio = ratio; };
	void setIllumination(bool mode) { this->illuminationMode = mode; };
};

#endif // !TUNNEL_H_

