#include "header.h"

#ifndef CAMERA_H
#define CAMERA_H
#pragma once

class Camera : public Actor
{
private:
	GLFWwindow *window;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

public:
	Camera(GLFWwindow *window);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void processInput();
};

#endif