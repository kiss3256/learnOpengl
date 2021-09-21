#include "header.h"

#ifndef CUBE_H
#define CUBE_H
#pragma once

class Cube
{
private:
	GLuint VAO, VBO;
	GLuint texture;

public:
	Cube(const char *textureName);
	~Cube();

	void render();
};
#endif