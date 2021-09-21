#include "Camera.hpp"

Camera::Camera(GLFWwindow *window_ptr, glm::vec3 &position, glm::vec3 &target)
{

    window = window_ptr;
    location = position;
    direction = target;

    std::cout << "LOG::Camera created." << std::endl;

    std::cout << "LOG::Camera location: ( " << location.x << ", " << location.y << ", " << location.z << " )." << std::endl;
    std::cout << "LOG::Camera rotation: ( " << rotation.x << ", " << rotation.y << ", " << rotation.z << " )." << std::endl;
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(location, direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix()
{
    int scrWidth, scrHeight;
    glfwGetWindowSize(window, &scrWidth, &scrHeight);
    return glm::perspective(glm::radians(45.0f), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
}

void Camera::moveForward(float value)
{
    location.z += value;
    direction.z += value;
}

// void Camera::moveRight(float value)
// {
//     location.x += value;
//     direction.x += value;

//     std::cout << "LOG::Camera location: ( " << location.x << ", " << location.y << ", " << location.z << " )." << std::endl;
//     std::cout << "LOG::Camera direction: ( " << direction.x << ", " << direction.y << ", " << direction.z << " )." << std::endl;
// }