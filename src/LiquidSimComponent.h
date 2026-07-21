#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h";

class LiquidSimComponent {
public:

	LiquidSimComponent();
	~LiquidSimComponent();

	void Draw(Shader& shader);
	float getWidth() { return width; };
	float getLength() { return length; };
	float getHeight() { return height; };
	void Resize(unsigned int width, unsigned int length, unsigned int height);

private:

	float width, length, height;

	Mesh cage{ "models/cage.obj" };

	std::vector<glm::vec3> points;

};