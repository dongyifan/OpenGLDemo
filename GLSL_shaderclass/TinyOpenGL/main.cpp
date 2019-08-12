//
//  main.cpp
//  TinyOpenGL
//
//  Created by DongYifan on 6/26/15.
//  Copyright (c) 2015 vanille. All rights reserved.
//

#include <iostream>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};


int main(int argc, const char * argv[]) {
    glfwInit();
    
    int Major, Minor, Rev;
    
    
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwGetVersion(&Major, &Minor, &Rev);
    
    printf("GLFW %d.%d.%d initialized\n", Major, Minor, Rev);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    
    printf("%s\n", glGetString(GL_VERSION));
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    Shader ourShader("vertex.glsl", "fragment.glsl");
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
//        float timeValue = glfwGetTime();
//        float greenValue = std::sin(timeValue) / 2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
