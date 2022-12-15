#include "TextureLoader.h"
#include <stb_image.h>

TextureLoader::TextureLoader() {
	init();
}

void TextureLoader::init() {
	int WIDTH, HEIGHT, COMP;

	//FLOOR TEXTURE
	std::string filepath = std::string(TEXTURE_DIR) + std::string("floor_texture.png");
	auto data = stbi_load(filepath.c_str(), &WIDTH, &HEIGHT, &COMP, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "TEXTURE NOT LOADED" << std::endl;
	}

	// Generate the texture
	GLuint tex;
	glGenTextures(1, &tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);


	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	//CUBE TEXTURE
	std::string filepath_cube = std::string(TEXTURE_DIR) + std::string("cube_texture.png");
	data = stbi_load(filepath_cube.c_str(), &WIDTH, &HEIGHT, &COMP, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "TEXTURE NOT LOADED" << std::endl;
	}
	// generate the texture
	GLuint tex_cube;
	glGenTextures(1, &tex_cube);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);

	//Image to GPU
	for (unsigned int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8,
			WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}


	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


	//param texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	stbi_image_free(data);
}