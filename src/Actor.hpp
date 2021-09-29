#include "header.h"

#ifndef ACTOR_H
#define ACTOR_H
#pragma once

using glm::vec3;

class Actor
{
private:
public:
	Actor();
	virtual ~Actor();

	vec3 location;
	vec3 rotation;
	vec3 scale;

	void setLocation(const glm::vec3 &location) { this->location = location; };
	void setRotation(const glm::vec3 &rotation) { this->rotation = rotation; };
	void setScale(const glm::vec3 &scale) { this->scale = scale; };
	void setScale(const float scale) { this->scale *= scale; };

	void moveForward(float value);
	void moveRight(float value);
	void moveUp(float value);
};

#endif