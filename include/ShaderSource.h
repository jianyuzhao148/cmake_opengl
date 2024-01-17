#ifndef __SHADERSOURCE__
#define __SHADERSOURCE__

#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <iostream>

class ShaderSource{
    public:
    const char* vertexPath;
    const char* fragmentPath;
    GLuint id;

    public:
    ShaderSource(const char* vertexPath,const char* fragmentPath);
    void compile();
    ~ShaderSource();
};
#endif