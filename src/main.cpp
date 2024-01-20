#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ShaderSource.h>
#include <lua.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Hello OpenGL"

int main(){
    if(!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);
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

    ShaderSource shaderSource("../resource/vertex.vs","../resource/fragment.fs");
    shaderSource.compile();
    
    GLfloat vertex[] = {
        -0.5f,-0.5f,0.0f,   0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f,     0.0f,0.5f,0.0f,
        0.5,-0.5f,0.0f,     0.5f,0.0f,0.5f,
        0.0f,-0.5f,0.5f,   0.0f,0.5f,0.0f,
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 mode(1.0f);
        mode = glm::rotate(mode, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shaderSource.id, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mode));
        glEnable(GL_DEPTH_TEST);
        glUseProgram(shaderSource.id);
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
