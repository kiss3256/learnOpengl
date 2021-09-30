#include "header.h"

#ifndef CUBE_H
#define CUBE_H
#pragma once

class Cube : public Actor
{
private:
	GLuint VAO, VBO;
	GLuint diffuseMap;
	GLuint specularMap;

public:
	Program *program;

	Cube();
	Cube(const char *texture);
	Cube(const char *diffuse, const char *specular);
	~Cube();

	void render(Camera *camera);

	void setProgram(Program *newProgram);
};
#endif