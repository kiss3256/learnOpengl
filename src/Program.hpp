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

	inline void use() { glUseProgram(program); }
};

#endif