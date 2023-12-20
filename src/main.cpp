#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello OpenGL"

int main(){
    if(!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_TITLE,nullptr,nullptr);
    if(!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    
    GLfloat vertex[] = {
        -0.5f,-0.5f,0.0f, 0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f,   0.0f,0.5f,0.0f,
        0.5,-0.5f,0.0f,   0.5f,0.0f,0.5f,
        0.0f,-0.5f,-0.5f,   0.0f,0.5f,0.0f,
    };
    GLuint index[]={
        0,1,2,
        2,1,3,
        3,0,1
    };

    GLuint VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint IBO;
    glGenBuffers(1,&IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}