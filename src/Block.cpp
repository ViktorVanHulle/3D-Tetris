#include "Block.h"

Block::Block() {
	this->window = Window::getInstance();
	x_coord = 5;
	y_coord = 5;
	z_coord = 1;
}
Block::Block(int x, int y, int z) {
	this->window = Window::getInstance();
	x_coord = x;
	y_coord = y;
	z_coord = z;
}

void Block::createBlock() {

	shader = std::make_shared<Shader>();
	shader->makeShaderProgram(vertexShaderSourceCube, fragmentShaderSourceCube);
	block_program = shader->getShaderProgram();

	unsigned int VBO;

	glGenVertexArrays(1, &blockVAO);
	glGenBuffers(1, &VBO);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(blockVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);


	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void Block::drawActiveBlock() {


	GLfloat blueColor[] = {
		0.0f, 0.0f, 1.0f,
	};//Blue

	GLfloat darkBlueColor[] = {
	0.0f, 0.0f, 139.0f / 256.0f
	};//Blue

	//COLOR
	int vertexColorLocation = glGetUniformLocation(block_program, "ourColor");

	float posX = 3.0f - (float)x_coord;
	float posY = 3.0f - (float)y_coord;
	float posZ = 5.5f - (float)z_coord;

	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	projection = glm::perspective(glm::radians(45.0f),  window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));



	glUseProgram(block_program);
	glBindVertexArray(blockVAO);

	glUniformMatrix4fv(glGetUniformLocation(block_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(block_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(block_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(glGetUniformLocation(block_program, "texRatio"), 0.0f);
	glUniform1f(glGetUniformLocation(block_program, "transparency"), 0.3f);
	glUniform4fv(vertexColorLocation, 1, blueColor);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniform4fv(vertexColorLocation, 1, darkBlueColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUniform4fv(vertexColorLocation, 1, blueColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Block::drawSolidBlock() {

	GLfloat blueColor[] = {
	0.0f, 0.0f, 1.0f,
	};//Blue

	//COLOR
	int vertexColorLocation = glGetUniformLocation(block_program, "ourColor");

	float posX = 3.0f - (float)x_coord;
	float posY = 3.0f - (float)y_coord;
	float posZ = 5.5f - (float)z_coord;

	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	projection = glm::perspective(glm::radians(45.0f),  window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(block_program);
	glBindVertexArray(blockVAO);

	glUniformMatrix4fv(glGetUniformLocation(block_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(block_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(block_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(glGetUniformLocation(block_program, "texRatio"), 0.0f);
	glUniform1f(glGetUniformLocation(block_program, "transparency"), 1.0f);

	glUniform4fv(vertexColorLocation, 1, blueColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Block::moveTile(int key) {

	//float len = 1.0f / 5.0f;

	if (key == GLFW_KEY_UP) {
		if (y_coord > 1)
			y_coord--;
	}
	if (key == GLFW_KEY_DOWN) {
		if (y_coord < 5)
			y_coord++;
	}
	if (key == GLFW_KEY_LEFT) {
		if (x_coord < 5)
			x_coord++;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (x_coord > 1)
			x_coord--;
	}
	if (key == GLFW_KEY_X) {
		if (z_coord + 1 < 11.0f)
			z_coord++;
		if (z_coord == 10.0f) {
			active = false;
		}
	}
}