#include "Program.hpp"

Program::Program(Shader *vertexShader, Shader *fragmentShader)
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader->shader);
    glAttachShader(program, fragmentShader->shader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

Program::~Program() { glDeleteProgram(program); }

void Program::use() { glUseProgram(program); }

void Program::setUniform(const char *uniform, float *value)
{
    GLint location = glGetUniformLocation(program, uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}