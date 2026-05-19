#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int main(void) 
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "FlapChud", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window,
        (mode->width - screenWidth) / 2,
        (mode->height - screenHeight) / 2
    );

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Game game(window, screenWidth, screenHeight);

    while (game.isRunning())
    {
        game.update();
        game.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}