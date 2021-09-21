#include "header.h"

#ifndef CAMERA_H
#define CAMERA_H
#pragma once

class Camera : public Actor
{
private:
	glm::vec3 location;
	glm::vec3 direction;
	GLFWwindow *window;

public:
	Camera(GLFWwindow *window, glm::vec3 &position, glm::vec3 &target);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void moveForward(float value);
	// void moveRight(float value);
};

#endif