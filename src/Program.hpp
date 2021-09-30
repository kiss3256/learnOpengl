#include "header.h"

#ifndef PROGRAM_H
#define PROGRAM_H
#pragma once

class Program
{
private:
	GLuint program;

public:
	Program(Shader *vertexShader, Shader *fragmentShader);
	~Program();

	void use();

	void setUniform(const char *uniform, const float *value);
	void setUniform(const char *uniform, glm::vec3 value);
	void setUniform(const char *uniform, float value);
};

#endif