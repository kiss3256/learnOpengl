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
	// void setUniform(const char *uniform, int value);
};

#endif