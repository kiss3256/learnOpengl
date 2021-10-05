#include "header.h"

#ifndef MESH_H
#define MESH_H
#pragma once

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(Program &program);

private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};
#endif