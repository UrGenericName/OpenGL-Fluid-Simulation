#pragma once

#include "EBO.h"
#include "VAO_line.h"
#include "VBO_line.h"
#include "shaderClass.h"

using namespace std;

class Lines {
public:

	vector<LineVertex> vertices;
	vector<GLuint> indices;

	Lines();
	~Lines();

	void Draw(Shader& shader);
	void updateBuffers();

private:

	VAO_line VAO;
	VBO_line* VBOptr;
	EBO* EBOptr;

	void LineSetup();

};