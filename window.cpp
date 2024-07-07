#include <GLFW/glfw3.h>
#include <iostream>

int main() {

    if (!glfwInit())
        return -1;
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "Test", NULL, NULL);


    if (window == NULL) {
        std::cout << "Failed To Create Window";

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
