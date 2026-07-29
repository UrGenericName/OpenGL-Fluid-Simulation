#pragma once

#include <string>
#include <functional>
#include "VAO.h"
#include "EBO.h"
#include "ShaderClass.h"

class Scene;
class SSBOcomponent;
class Lines;

class Mesh {
public:

	friend Scene;
	friend SSBOcomponent;
	friend Lines;

	glm::vec3 position { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale { 1.0f, 1.0f, 1.0f };

	float emissive = 0.0f;

	std::string fileName;
	glm::vec3 tint;

	Mesh(std::string fileName, glm::vec3 importColor = { 1.0f, 1.0f, 1.0f }, float i_emissive = 0.0f);
	Mesh(const Mesh& other);
	~Mesh();

	void Draw(Shader& shader);
	bool importObj(std::string fileName, glm::vec3 importColor);	// imports an obj mesh (MUST BE TRIANGLATED BEFORE IMPORT)
	void updateBuffers();

	glm::mat4 getModelMatrix();

	glm::mat4 getTranslationMatrix();
	glm::mat4 getRotationMatrix();
	glm::mat4 getScaleMatrix();

private:

	VAO VAO;
	VBO* VBOptr;
	EBO* EBOptr;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	void MeshSetup();
};