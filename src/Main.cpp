#include "Main.h"

int main(int argc, char** argv) {

    Window& window = Window::getInstance(); // initialize the singleton

    try {
        // cmd(printed last in the help text, delimiter, version number, disable default arguments)
        TCLAP::CmdLine cmd("Command description message", ' ', "0.9", false);

        TCLAP::ValueArg<int> widthArg("w", "width", "configure the width of the window", false, 800, "int");
        TCLAP::ValueArg<int> heightArg("g", "height", "configure the height of the window", false, 800, "int");

        cmd.add(widthArg);
        cmd.add(heightArg);

        // Parse the argv array.
        cmd.parse(argc, argv);

        window.SCREEN_WIDTH = widthArg.getValue();
        window.SCREEN_HEIGHT = heightArg.getValue();
    }
    catch (TCLAP::ArgException& e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        return 1;
    }

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