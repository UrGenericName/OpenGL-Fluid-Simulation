#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Lines.h"

class LiquidSimComponent {
public:

	LiquidSimComponent();
	~LiquidSimComponent();

	void Draw(Shader& shader, Shader& lineShader);
	float getWidth() { return width; };
	float getLength() { return length; };
	float getHeight() { return height; };
	void Resize(float width, float length, float height);

private:

	float width, length, height;

	Lines lines;
	Mesh cage{ "models/cage.obj" };

	std::vector<glm::vec3> points;

};