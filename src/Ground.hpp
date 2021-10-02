#include "header.h"
#ifndef GROUND_H
#define GROUND_H
#pragma once

class Ground
{
private:
	GLuint VAO, VBO;
	GLuint groundProgram;

public:
	Ground();
	~Ground();

	void draw(Camera *mainCamera);
};
#endif