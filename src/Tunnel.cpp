#include "Tunnel.h"

Tunnel::Tunnel() {
	this->window = Window::getInstance();

}
void Tunnel::createTunnel()
{
	createFarWall();
	createSideWall();
	createSideWall();
	createSideWall();
	createSideWall();
}

void Tunnel::createFarWall() {

	shader = std::make_shared<Shader>();
	shader->makeShaderProgram(vertexShaderSource, fragmentShaderSource);
	tunnel_program = shader->getShaderProgram();

	int ratio = 5;
	int ratioPlus = ratio + 1;
	int ratioPowV = pow(ratio + 1, 2);
	int ratioPow = pow(ratio, 2);

	//VERTEX & INDEX ARRAY
	float vertices[36 * 2];
	unsigned int indices_white[25 * 6];
	unsigned int indices_black[25 * 6];

	//length of cube
	float len = 1.0f / 5.0f;

	//array of vertices
	for (int y = 0; y < ratioPlus; y++) {
		for (int x = 0; x < ratioPlus; x++) {
			vertices[(y * ratioPlus + x) * 2] = -0.5f + len * x;
			vertices[(y * ratioPlus + x) * 2 + 1] = 0.5f - len * y;
		}
	}

	//array of indices
	for (int i = 0; i < ratioPow; i++) {
		int r = i / ratio;
		int c = i % ratio;
		if (i % 2) {
			indices_white[i * 6] = c + r * ratioPlus;
			indices_white[i * 6 + 1] = c + 1 + r * ratioPlus;
			indices_white[i * 6 + 2] = c + (ratio + 2) + r * ratioPlus;

			indices_white[i * 6 + 3] = c + r * ratioPlus;
			indices_white[i * 6 + 4] = c + (ratio + 1) + r * ratioPlus;
			indices_white[i * 6 + 5] = c + (ratio + 2) + r * ratioPlus;
		}
		else {
			indices_black[i * 6] = c + r * ratioPlus;
			indices_black[i * 6 + 1] = c + 1 + r * ratioPlus;
			indices_black[i * 6 + 2] = c + (ratio + 2) + r * ratioPlus;

			indices_black[i * 6 + 3] = c + r * ratioPlus;
			indices_black[i * 6 + 4] = c + (ratio + 1) + r * ratioPlus;
			indices_black[i * 6 + 5] = c + (ratio + 2) + r * ratioPlus;
		}
	}


	float vertices_texture[36 * 2];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			vertices_texture[(i * 6 + j) * 2] = 0.0f + len * j;
			vertices_texture[(i * 6 + j) * 2 + 1] = 1.0f - len * i;
		}
	}

	float vertices_normal[36 * 3];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			vertices_normal[(i * 6 + j) * 3] = 0.0f;
			vertices_normal[(i * 6 + j) * 3 + 1] = 0.0f;
			vertices_normal[(i * 6 + j) * 3 + 2] = 1.0f;
		}
	}


	unsigned int VBO, VBO_textures, VBO_normal;

	glGenVertexArrays(1, &farVAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(farVAO);


	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_textures);
	glGenBuffers(1, &VBO_normal);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO_whiteFar);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_whiteFar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_white), indices_white, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO_blackFar);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_blackFar);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_white), indices_black, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_texture), vertices_texture, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_normal), vertices_normal, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);	
}

void Tunnel::createSideWall() {

	shader = std::make_shared<Shader>();
	shader->makeShaderProgram(vertexShaderSource, fragmentShaderSource);
	tunnel_program = shader->getShaderProgram();

	//VERTEX & INDEX ARRAY
	float vertices[121 * 2];
	unsigned int indices_white[100 * 6];
	unsigned int indices_black[100 * 6];

	//length of cube
	float len = 1.0f / 10.0f;

	//array of vertices
	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 11; x++) {
			vertices[(y * 11 + x) * 2] = -0.5f + len * x;
			vertices[(y * 11 + x) * 2 + 1] = 0.5f - len * y;
		}
	}

	//array of indices
	for (int r = 0; r < 5; r++) {
		for (int i = 0; i < 5; i++) {

			if (r % 2) {
				//WHITE SQUARE
				//upper triangle
				indices_white[(r * 10 + i) * 6] = r * 10 + r + (i * 2);
				indices_white[(r * 10 + i) * 6 + 1] = r * 10 + r + (i * 2) + 1;
				indices_white[(r * 10 + i) * 6 + 2] = r * 10 + r + (i * 2) + 12;
				//bottom triangle
				indices_white[(r * 10 + i) * 6 + 3] = r * 10 + r + (i * 2);
				indices_white[(r * 10 + i) * 6 + 4] = r * 10 + r + (i * 2) + 12;
				indices_white[(r * 10 + i) * 6 + 5] = r * 10 + r + (i * 2) + 11;

				///BLACK SQUARE
				//upper triangle
				indices_black[(r * 10 + i) * 6] = r * 10 + r + (i * 2) + 1;
				indices_black[(r * 10 + i) * 6 + 1] = r * 10 + r + (i * 2) + 2;
				indices_black[(r * 10 + i) * 6 + 2] = r * 10 + r + (i * 2) + 13;
				//bottom triangle
				indices_black[(r * 10 + i) * 6 + 3] = r * 10 + r + (i * 2) + 1;
				indices_black[(r * 10 + i) * 6 + 4] = r * 10 + r + (i * 2) + 13;
				indices_black[(r * 10 + i) * 6 + 5] = r * 10 + r + (i * 2) + 12;
			}
			else {
				//WHITE SQUARE
				//upper triangle
				indices_black[(r * 10 + i) * 6] = r * 10 + r + (i * 2);
				indices_black[(r * 10 + i) * 6 + 1] = r * 10 + r + (i * 2) + 1;
				indices_black[(r * 10 + i) * 6 + 2] = r * 10 + r + (i * 2) + 12;
				//bottom triangle
				indices_black[(r * 10 + i) * 6 + 3] = r * 10 + r + (i * 2);
				indices_black[(r * 10 + i) * 6 + 4] = r * 10 + r + (i * 2) + 12;
				indices_black[(r * 10 + i) * 6 + 5] = r * 10 + r + (i * 2) + 11;

				///BLACK SQUARE
				//upper triangle
				indices_white[(r * 10 + i) * 6] = r * 10 + r + (i * 2) + 1;
				indices_white[(r * 10 + i) * 6 + 1] = r * 10 + r + (i * 2) + 2;
				indices_white[(r * 10 + i) * 6 + 2] = r * 10 + r + (i * 2) + 13;
				//bottom triangle
				indices_white[(r * 10 + i) * 6 + 3] = r * 10 + r + (i * 2) + 1;
				indices_white[(r * 10 + i) * 6 + 4] = r * 10 + r + (i * 2) + 13;
				indices_white[(r * 10 + i) * 6 + 5] = r * 10 + r + (i * 2) + 12;
			}


		}

	}

	float vertices_texture[121 * 2];
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			vertices_texture[(i * 11 + j) * 2] = 0.0f + len * j;
			vertices_texture[(i * 11 + j) * 2 + 1] = 1.0f - len * i;
		}
	}

	float vertices_normal[36 * 3];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			vertices_normal[(i * 6 + j) * 3] = 0.0f;
			vertices_normal[(i * 6 + j) * 3 + 1] = 0.0f;
			vertices_normal[(i * 6 + j) * 3 + 2] = 1.0f;
		}
	}

	float vertices_normal2[36 * 3];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			vertices_normal2[(i * 6 + j) * 3] = 0.0f;
			vertices_normal2[(i * 6 + j) * 3 + 1] = 0.0f;
			vertices_normal2[(i * 6 + j) * 3 + 2] = -1.0f;
		}
	}


	unsigned int VBO, VBO_textures, VBO_normal, VBO_normal2;

	glGenVertexArrays(1, &sideVAO);
	glGenVertexArrays(1, &side2VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_textures);
	glGenBuffers(1, &VBO_normal);
	glGenBuffers(1, &VBO_normal2);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//sideVAO
	glBindVertexArray(sideVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO_white);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_white), indices_white, GL_STATIC_DRAW);


	glGenBuffers(1, &EBO_black);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_black), indices_black, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_texture), vertices_texture, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_normal), vertices_normal, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);


	glBindVertexArray(0);



	//side2VAO
	glBindVertexArray(side2VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO_white);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_white), indices_white, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO_black);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_black), indices_black, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_texture), vertices_texture, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_normal2), vertices_normal2, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);


	glBindVertexArray(0);

}


void Tunnel::drawTunnel()
{

	drawFarWall();
	drawSideWall_L();
	drawSideWall_R();
	drawSideWall_T();
	drawSideWall_B();
}



void Tunnel::drawFarWall() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(tunnel_program, "ourColor");
	//UNIFORM
	//double timeValue = glfwGetTime();
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White

	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	projection = glm::perspective(glm::radians(45.0f), window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	glUseProgram(tunnel_program);
	glBindVertexArray(farVAO);

	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(tunnel_program, "texRatio"), texture_ratio);
	glUniform1f(glGetUniformLocation(tunnel_program, "illuminationMode"), illuminationMode);
	glUniform3fv(glGetUniformLocation(tunnel_program, "lightColor"), 1, whiteColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_whiteFar);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_blackFar);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);
}

void Tunnel::drawSideWall_L() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(tunnel_program, "ourColor");
	//UNIFORM
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White


	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	model = glm::translate(model, glm::vec3(-2.5f, -2.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	projection = glm::perspective(glm::radians(45.0f), window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUseProgram(tunnel_program);
	glBindVertexArray(sideVAO);


	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(tunnel_program, "texRatio"), texture_ratio);
	glUniform1f(glGetUniformLocation(tunnel_program, "illuminationMode"), illuminationMode);
	glUniform3fv(glGetUniformLocation(tunnel_program, "lightColor"), 1, whiteColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);
}

void Tunnel::drawSideWall_R() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(tunnel_program, "ourColor");
	//UNIFORM
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White


	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(2.5f, -2.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	projection = glm::perspective(glm::radians(45.0f), window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));



	glUseProgram(tunnel_program);
	glBindVertexArray(side2VAO);


	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(tunnel_program, "texRatio"), texture_ratio);
	glUniform1f(glGetUniformLocation(tunnel_program, "illuminationMode"), illuminationMode);
	glUniform3fv(glGetUniformLocation(tunnel_program, "lightColor"), 1, whiteColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);
}

void Tunnel::drawSideWall_T() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(tunnel_program, "ourColor");
	//UNIFORM
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White


	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(-2.5f, 2.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	projection = glm::perspective(glm::radians(45.0f), window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));



	glUseProgram(tunnel_program);
	glBindVertexArray(sideVAO);


	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(tunnel_program, "texRatio"), texture_ratio);
	glUniform1f(glGetUniformLocation(tunnel_program, "illuminationMode"), illuminationMode);
	glUniform3fv(glGetUniformLocation(tunnel_program, "lightColor"), 1, whiteColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);
}

void Tunnel::drawSideWall_B() {

	//COLOR
	int vertexColorLocation = glGetUniformLocation(tunnel_program, "ourColor");
	//UNIFORM
	GLfloat blackColor[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};//Black
	GLfloat whiteColor[] = {
		1.0f, 1.0f, 1.0f, 1.0f
	};//White


	//Camera
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	model = glm::translate(model, glm::vec3(-2.5f, -2.5f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	projection = glm::perspective(glm::radians(45.0f), window.SCREEN_WIDTH / window.SCREEN_HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));



	glUseProgram(tunnel_program);
	glBindVertexArray(side2VAO);


	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(tunnel_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(glGetUniformLocation(tunnel_program, "texRatio"), texture_ratio);
	glUniform1f(glGetUniformLocation(tunnel_program, "illuminationMode"), illuminationMode);
	glUniform3fv(glGetUniformLocation(tunnel_program, "lightColor"), 1, whiteColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_white);
	glUniform4fv(vertexColorLocation, 1, whiteColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_black);
	glUniform4fv(vertexColorLocation, 1, blackColor);

	glDrawElements(GL_TRIANGLES, 128 * 3, GL_UNSIGNED_INT, 0);
}


