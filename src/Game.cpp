#include "Game.h"

void Game::init()
{
    //Window
    window->windowCreator();
    //Renderer
    gameRenderer = new GameRenderer();
    //Camera

    //glUseProgram(gameRenderer->getTunnel()->getTunnelProgram());
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
        //bg color
        glClearColor(0.128f, 0.128f, 0.128f, 1.0f);

        //CODE HERE
        gameRenderer->renderer();

        /* Swap front and back buffers */
        glfwSwapBuffers(window->winWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
