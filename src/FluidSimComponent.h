#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Lines.h"
#include "ShaderPipelineComponent.h"

class FluidSimComponent {
public:

	ShaderPipelineComponent shaderPipelineComponent;

	FluidSimComponent();
	~FluidSimComponent();

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