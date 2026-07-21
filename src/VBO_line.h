#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

struct LineVertex {

	glm::vec4 position;
	glm::vec4 color;

};

class VBO_line {
public:
	GLuint ID;
	VBO_line(std::vector<LineVertex>& vertices);

	void Update(std::vector<LineVertex>& vertices);
	void Bind();
	void Unbind();
	void Delete();
};