#include "ShaderSource.h"

// 文件读取
std::string getFileContext(const char* filePath) {
	std::ifstream fileStream;
	std::stringstream sstream;
	std::string returnStr;
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fileStream.open(filePath);
		sstream<<fileStream.rdbuf();
		fileStream.close();
		returnStr = sstream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return returnStr;
}

ShaderSource::ShaderSource(const char *vertexPath, const char *fragmentPath)
    :vertexPath(vertexPath),fragmentPath(fragmentPath)
{
}

void ShaderSource::compile()
{
    std::string vertexStr = getFileContext(vertexPath);
    const char* vertexContext = vertexStr.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexContext,NULL);
    glCompileShader(vertexShader);
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
        std::cout<<infoLog<<std::endl;
    }

    std::string fragmentStr = getFileContext(fragmentPath);
    const char* fragmentContext= fragmentStr.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentContext,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,nullptr,infoLog);
        std::cout<<infoLog<<std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id,vertexShader);
    glAttachShader(id,fragmentShader);
    glLinkProgram(id);
    glGetShaderiv(id,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(id,512,nullptr,infoLog);
        std::cout<<infoLog<<std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(id);
}

ShaderSource::~ShaderSource()
{
    glDeleteProgram(id);
}
