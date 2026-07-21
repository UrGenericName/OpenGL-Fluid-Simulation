#pragma once

#include <glad/glad.h>
#include "VBO_line.h"

class VAO_line {
public:
	GLuint ID;
	VAO_line();

	void LinkAttribute(VBO_line& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};