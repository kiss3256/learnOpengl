#include "Program.hpp"

Program::Program(const char *vs, const char *fs)
{
    Shader vertexShader(AssetsLoader(vs).getPath());
    Shader fragmentShader(AssetsLoader(fs).getPath());
    program = glCreateProgram();
    glAttachShader(program, vertexShader.shader);
    glAttachShader(program, fragmentShader.shader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::LINK_PROGRAM::" << infoLog << std::endl;
    }

    glDetachShader(program, vertexShader.shader);
    glDetachShader(program, fragmentShader.shader);

    std::cout << "LOG::Program created.\n";
}

Program::~Program()
{
    glDeleteProgram(program);
    std::cout << "LOG::Program deleted.\n";
}

void Program::use() { glUseProgram(program); }

void Program::setUniform(const char *uniform, const float *value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Program::setUniform(const char *uniform, glm::vec3 value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, uniform);
    glUniform3f(location, value.x, value.y, value.z);
}

void Program::setUniform(const char *uniform, float value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, uniform);
    glUniform1f(location, value);
}

void Program::setUniform(const char *uniform, int value)
{
    glUseProgram(program);
    GLint location = glGetUniformLocation(program, uniform);
    glUniform1i(location, value);
}