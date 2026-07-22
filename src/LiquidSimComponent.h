#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Lines.h"
#include "ShaderPipelineComponent.h"

class LiquidSimComponent {
public:

	ShaderPipelineComponent shaderPipelineComponent;

	LiquidSimComponent();
	~LiquidSimComponent();

	float getWidth() { return width; };
	float getLength() { return length; };
	float getHeight() { return height; };
	void Resize(float width, float length, float height);

	void Draw(Camera& camera);

private:

	float width, length, height;

	Lines lines;
	Mesh cage{ "models/cage.obj" };

	std::vector<glm::vec4> particles;

};