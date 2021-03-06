#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>                 // glm::vec3
#include <glm/vec4.hpp>                 // glm::vec4
#include <glm/mat4x4.hpp>               // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssetsLoader.hpp"
#include "Shader.hpp"
#include "Program.hpp"
#include "Actor.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Ground.hpp"
#include "ObjectManager.hpp"
#include "stb_image.h"

#endif