#include "Game.h"

void Game::init()
{
    //Window
    window->windowCreator();
    //Renderer
    gameRenderer = new GameRenderer();
}

void Game::run()
{
    /* Initialize game */
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->winWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //CODE HERE


        /* Swap front and back buffers */
        glfwSwapBuffers(window->winWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
