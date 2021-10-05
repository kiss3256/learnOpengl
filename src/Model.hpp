#include "header.h"

#ifndef MODEL_H
#define MODEL_H
#pragma once

class Model
{
public:
	Model(const char *path);
	~Model();

	void Draw(Program &program);

private:
	std::vector<Texture> textures_loaded;

	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
#endif