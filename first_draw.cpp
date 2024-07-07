#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <iostream>


//vertex shader
char* vssource =
"#version 330 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main()                                            \    
 {                                                      \
    gl_Position = vec4(inPosition, 1.0);                \
 }";
//fragment shader
char* fssource =
"#version 330 core\n                                    \
 out vec4 fragColor;                                    \
 void main()                                            \    
 {                                                      \
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);           \
 }";

 float vertices[] = {
    -0.6f, -0.6f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

unsigned int programID;

int main() {
    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Test", NULL, NULL);

    glm::mat4 mat4;

    if (window == NULL) {
        std::cout << "Failed To Create Window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD";
        return -1;
    }

    programID = glCreateProgram();

    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderID, 1, &vssource, NULL);
    glCompileShader(vertexShaderID);

    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderID, 1, &fssource, NULL);
    glCompileShader(fragmentShaderID);


    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);

    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,(void*)0);

    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.4f, 0.7f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
