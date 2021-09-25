#include "header.h"

#ifndef CAMERA_H
#define CAMERA_H
#pragma once

class Camera : public Actor
{
private:
	GLFWwindow *window;

public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	Camera(GLFWwindow *window_ptr);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void processInput();
};

#endif