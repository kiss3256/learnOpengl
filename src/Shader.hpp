#include "header.h"

#ifndef SHADER_H
#define SHADER_H
#pragma once

class Shader
{
public:
    Shader(const char *filename, GLenum type);
    ~Shader();

    GLuint shader;
};
#endif