#pragma once

#include "EBO.h"
#include "VAO_line.h"
#include "VBO_line.h"
#include "shaderClass.h"
#include "Mesh.h"

using namespace std;

class Lines {
public:

	vector<LineVertex> vertices;
	vector<GLuint> indices;

	glm::vec3 position { 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale { 1.0f, 1.0f, 1.0f };

	glm::vec3 tint { 1.0f, 1.0f, 1.0f };

	Lines();
	Lines(Mesh& mesh);
	~Lines();

	void Draw(Shader& shader);
	void generateFromBoundingBox(Mesh& mesh);
	void updateBuffers();

	glm::mat4 getModelMatrix();

	glm::mat4 getTranslationMatrix();
	glm::mat4 getRotationMatrix();
	glm::mat4 getScaleMatrix();

private:

	VAO_line VAO;
	VBO_line* VBOptr;
	EBO* EBOptr;

	void LineSetup();

};