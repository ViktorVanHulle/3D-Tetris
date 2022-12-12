#include "Main.h"

int main() {
	openGLInit();
	Game* game = new Game();
	game->run();
	return 0;
}
/* OpenGL and GLFW initialization*/
void openGLInit() {

	//if (!glfwInit()) std::cout << "ERROR: GLFW failed to initialize!" << std::endl;
	//else std::cout << "GLFW initiliazed!" << std::endl;
	//WindowHints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}