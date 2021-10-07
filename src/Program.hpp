#include "header.h"

#ifndef PROGRAM_H
#define PROGRAM_H
#pragma once

class Program
{
private:
	GLuint program;

public:
	Program(const char *vs, const char *fs);
	~Program();

	void use();

	void setUniform(const char *uniform, const float *value);
	void setUniform(const char *uniform, glm::vec3 value);
	void setUniform(const char *uniform, float value);
	void setUniform(const char *uniform, int value);
};

#endif