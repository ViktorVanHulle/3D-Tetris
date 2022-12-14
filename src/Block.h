#ifndef BLOCK_H_
#define BLOCK_H_

#include "Externs.h"
#include "Shaders.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Block {
private:
	bool active = true;
	int x_coord;
	int y_coord;
	int z_coord;
	glm::vec4 color;
	GLuint block_program;
	std::shared_ptr<Shader> shader;
	//Window* window;
	unsigned int blockVAO;

	float vertices[108] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	};

public:
	Block();
	Block(int x, int y, int z);
	Window window;
	void createBlock();
	void drawActiveBlock();
	void drawSolidBlock();
	void boxCollision();
	void moveTile(int key);
	GLuint getBlockProgram() { return block_program; };
	unsigned int getVAO() { return blockVAO; };
	int getX() { return x_coord; };
	int getY() { return y_coord; };
	int getZ() { return z_coord; };
	void setZ(int z) { this->z_coord = z; };
	int getActive() { return active; };
	void setActive(bool state) { this->active = state; };
};

#endif // !BLOCK_H_
