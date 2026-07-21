#include "VAO_line.h"

VAO_line::VAO_line() {
	glGenVertexArrays(1, &ID);
}

void VAO_line::LinkAttribute(VBO_line& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO_line::Bind() {
	glBindVertexArray(ID);
}

void VAO_line::Unbind() {
	glBindVertexArray(0);
}

void VAO_line::Delete() {
	glDeleteVertexArrays(1, &ID);
}