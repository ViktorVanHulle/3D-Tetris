#include "Game.h"

void Game::init()
{
    //Window
    window.windowCreator();

    //Renderer
    gameRenderer = new GameRenderer();
}

void Game::run()
{
    /* Initialize game */
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.winWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //bg color
        glClearColor(0.128f, 0.128f, 0.128f, 1.0f);

        //CODE HERE
        gameRenderer->renderer();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.winWindow);

        /* Poll for and process events */
        glfwPollEvents();


        inputChecker();
    }

    glfwTerminate();
}

void Game::inputChecker() {
    
    timer();

    if (glfwGetKey(window.winWindow, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwTerminate();
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_UP) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_UP);
        gameRenderer->checkBoxCollision(GLFW_KEY_UP);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_DOWN) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_DOWN);
        gameRenderer->checkBoxCollision(GLFW_KEY_DOWN);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_LEFT) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_LEFT);
        gameRenderer->checkBoxCollision(GLFW_KEY_LEFT);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_RIGHT) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_RIGHT);
        gameRenderer->checkBoxCollision(GLFW_KEY_RIGHT);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_X) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_X);
        gameRenderer->checkBoxCollision(GLFW_KEY_X);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_SPACE) == GLFW_PRESS && pressed == false) {
        pressed = true;
        gameRenderer->checkBoxCollision(GLFW_KEY_SPACE);
    }
    else if (glfwGetKey(window.winWindow, GLFW_KEY_UP) == GLFW_RELEASE &&
        glfwGetKey(window.winWindow, GLFW_KEY_DOWN) == GLFW_RELEASE &&
        glfwGetKey(window.winWindow, GLFW_KEY_LEFT) == GLFW_RELEASE &&
        glfwGetKey(window.winWindow, GLFW_KEY_X) == GLFW_RELEASE &&
        glfwGetKey(window.winWindow, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
        glfwGetKey(window.winWindow, GLFW_KEY_SPACE) == GLFW_RELEASE
        && pressed == true) {
        pressed = false;
    }
}


void Game::timer() {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    passTime += deltaTime;


    if (passTime > 2.0f) {
        gameRenderer->getActiveBlock()->moveTile(GLFW_KEY_X);
        gameRenderer->checkBoxCollision(GLFW_KEY_X);
        lastFrame = currentFrame;
        passTime = 0.0f;
    }

}

