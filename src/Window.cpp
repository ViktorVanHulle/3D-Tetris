#include "Window.h"

unsigned int Window::windowCreator()
{
	/* Initialize GLFW */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    else { 
        std::cout << "GLFW initiliazed!" << std::endl; 
    }

	winWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blockout", NULL, NULL);

    /* instance window initialized */
	if (!winWindow) {
        std::cout << "Failed to initialize window" << std::endl;
		glfwTerminate();
		return -1;
	}

    /* Make the window's context current */
    glfwMakeContextCurrent(winWindow);

    //key callback
    //glfwSetKeyCallback(winWindow, &Window::key_callback);
    
    /* Initialize glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	return 0;
}