#pragma once
#include "VBO_line.h"

VBO_line::VBO_line(std::vector<LineVertex>& vertices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(LineVertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO_line::Update(std::vector<LineVertex>& vertices) {

	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(LineVertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO_line::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO_line::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_line::Delete() {
	glDeleteBuffers(1, &ID);
}