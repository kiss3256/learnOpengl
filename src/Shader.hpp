#include "header.h"

#ifndef SHADER_H
#define SHADER_H
#pragma once

class Shader
{
public:
    Shader(std::string filename);
    ~Shader();

    GLuint shader;
};
#endif