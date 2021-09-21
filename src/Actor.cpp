#include "Actor.hpp"

Actor::Actor()
{
    location = vec3(0.0f, 0.0f, 0.0f);
    rotation = vec3(0.0f, 0.0f, 0.0f);
    scale = vec3(1.0f, 1.0f, 1.0f);
    std::cout << "LOG::Actor created." << std::endl;
}

Actor::~Actor()
{
}

void Actor::moveForward(float value)
{
    location.z += value;
    std::cout << "LOG::Actor location: ( " << location.x << ", " << location.y << ", " << location.z << " )." << std::endl;
}

void Actor::moveRight(float value)
{
    location.x += value;
    std::cout << "LOG::Actor location: ( " << location.x << ", " << location.y << ", " << location.z << " )." << std::endl;
}

void Actor::moveUp(float value)
{
    location.y += value;
    std::cout << "LOG::Actor location: ( " << location.x << ", " << location.y << ", " << location.z << " )." << std::endl;
}