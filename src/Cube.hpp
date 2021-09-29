#include "header.h"

#ifndef CUBE_H
#define CUBE_H
#pragma once

class Cube : public Actor
{
private:
	GLuint VAO, VBO;
	GLuint texture;

	Program *program;

public:
	Cube(){};
	Cube(const char *textureName);
	~Cube();

	void render(Camera *camera);

	void setProgram(Program *program) { this->program = program; };
};
#endif